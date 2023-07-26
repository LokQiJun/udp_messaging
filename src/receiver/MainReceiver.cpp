#include "receiver/MainReceiver.h"
#include "streaming/VideoPlayer.h"
#include "concurrency/ThreadPool.h"
#include "UDPPacket/UDPPacket.h"
#include "utils.h"

#include <fstream>
#include <future>
#include <iostream>
#include <functional>
#include <opencv2/opencv.hpp>

void MainReceiver::packetHandler(std::vector<char>& buffer)
{
    //Extract data
    UDPHeader udpheader = removeHeader(buffer);
    std::map<int, std::vector<char>> completeMap; // only for files
   
    // Handle Stream
    if (strcmp(udpheader.filetype.c_str(), "stream") == 0)
    {       
        // Initalise maps for new stream 
        std::lock_guard<std::mutex> lock(mapMutex); // Obtain mutex
        if (filenameDataMap.find(udpheader.filename) == filenameDataMap.end()) {
            filenameDataMap[udpheader.filename] = std::map<int, std::vector<char>>();
        }
        if (streamFrameOrderMap.find(udpheader.filename) == streamFrameOrderMap.end()) {
            streamFrameOrderMap[udpheader.filename] = udpheader.frameOrder;
        }

        // Check frame order 
        // incoming frame has same frame order as current frame, packet corresponds to current frame
        if (streamFrameOrderMap[udpheader.filename] == udpheader.frameOrder) 
        {
            // append new data to map
            filenameDataMap[udpheader.filename][udpheader.packetOrder] = buffer;
        }
        // incoming frame is of large frame order than current frame, remaining packets of current frames lost
        else if (streamFrameOrderMap[udpheader.filename] < udpheader.frameOrder || streamFrameOrderMap[udpheader.filename] == 1 ) 
        {
            // clear packets of current frame and append packet of new frame to map
            filenameDataMap[udpheader.filename] = std::map<int, std::vector<char>>(); 
            filenameDataMap[udpheader.filename][udpheader.packetOrder] = buffer;
            
            // update frame order for current stream
            streamFrameOrderMap[udpheader.filename] = udpheader.frameOrder;
        }
        // incoming frame is of smaller frame order than current frame, packet arrived late and is not needed anymore
        else
        {
            // drop packet by not processing
            return;
        }

        // Create a thread safe copy of the map with all relevant data        
        if (filenameDataMap[udpheader.filename].size() >= udpheader.numPackets)
        {
            std::vector<char> frameBuffer;
            for (auto& pair : filenameDataMap[udpheader.filename])
            {
                frameBuffer.insert(frameBuffer.end(), pair.second.begin(), pair.second.end());
            }
            cv::Mat frame = cv::imdecode(frameBuffer, cv::IMREAD_COLOR);
            VideoPlayer* videoPlayerInstance = VideoPlayer::getInstance();
            videoPlayerInstance -> newFrame(udpheader.filename, frame);
            
            
        }
        // Release mutex
    }

    // Handle file and message transfer
    else 
    {
        std::lock_guard<std::mutex> lock(mapMutex); // Obtain mutex
        if (filenameDataMap.find(udpheader.filename) == filenameDataMap.end()) 
        {
            filenameDataMap[udpheader.filename] = std::map<int, std::vector<char>>();
        }
        filenameDataMap[udpheader.filename][udpheader.packetOrder] = buffer;

        // Create a thread safe copy of the map with all relevant data                
        if (filenameDataMap[udpheader.filename].size() >= udpheader.numPackets)
        {
            completeMap = filenameDataMap[udpheader.filename];
            filenameDataMap.erase(udpheader.filename); 
        }
        // Release mutex
    }

    if (!completeMap.empty())
    {
        // text message
        if (strcmp(udpheader.filetype.c_str(), "message") == 0)
        {
            for (const auto& pair : completeMap)
            {
                std::cout << "\nPacket " << pair.first << ": " << std::string(pair.second.begin(), pair.second.end()) << std::endl;
            }
            std::cout << "Message Received." << std::endl;
        }
        // files
        else 
        {
            std::cout << "Writing file..." << std::endl;
            std::string filepath = "storage/" + datetimeToFilename() + "." + udpheader.filetype;
            std::ofstream outputfile(filepath, (std::ios::binary | std::ios::app));
            if (!outputfile.is_open())
            {
                std::cerr << "Failed to open file." << std::endl;
                return;
            }

            for (const auto& pair: completeMap)
            {
                outputfile.write(pair.second.data(), pair.second.size());
            }

            outputfile.close();
            std::cout << "File received with " << completeMap.size() << " packets and stored as " << filepath << std::endl;
        }
    }
}

void MainReceiver::run()
{
    int count = 0;
    while (true)
    {
        std::vector<char> buffer(PACKET_SIZE); 
        server -> receivePackets(buffer); // busy waits for packets
        count++;
        if (count % 100 == 0)
        {
            std::cout << count << ", ";
        }

        pool -> joinQueue(
            [this, buffer]() mutable 
            {
                packetHandler(buffer);
            }
        );
    }  
}