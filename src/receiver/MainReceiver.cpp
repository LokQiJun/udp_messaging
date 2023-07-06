#include "receiver/MainReceiver.h"

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
    std::map<int, std::vector<char>> completeMap;

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
        if (streamFrameOrderMap[udpheader.filename] == udpheader.frameOrder) // packet corresponds to current frame
        {
            // append new data to map
            filenameDataMap[udpheader.filename][udpheader.packetOrder] = buffer;
        }
        else if (streamFrameOrderMap[udpheader.filename] < udpheader.frameOrder) // remaining packets of current frames lost
        {
            // clear packets of current frame and append new data to map
            filenameDataMap[udpheader.filename] = std::map<int, std::vector<char>>(); 
            filenameDataMap[udpheader.filename][udpheader.packetOrder] = buffer;
            
            // update frame order for current stream
            streamFrameOrderMap[udpheader.filename] = udpheader.frameOrder;
        }
        else
        {
            // drop packet if it belongs to an older frame
        }

        // Create a thread safe copy of the map with all relevant data        
        if (filenameDataMap[udpheader.filename].size() >= udpheader.numPackets)
        {
            completeMap = filenameDataMap[udpheader.filename];
            filenameDataMap.erase(udpheader.filename); 
        }
        // Release mutex
    }

    // Handle file and message transfer
    else 
    {
        std::lock_guard<std::mutex> lock(mapMutex); // Obtain mutex
        if (filenameDataMap.find(udpheader.filename) == filenameDataMap.end()) {
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
        // // stream
        // else if (strcmp(udpheader.filetype.c_str(), "stream") == 0)
        // {
        //     std::vector<char> frameBuffer;
        //     for (const auto& pair : completeMap)
        //     {
        //         const std::vector<char>& packetBuffer = pair.second;
        //         frameBuffer.insert(frameBuffer.end(), packetBuffer.begin(), packetBuffer.end());
        //     }
        // }
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
    return;
}
void MainReceiver::run()
{
    while (true)
    {
        std::vector<char> buffer(PACKET_SIZE); 
        server -> receivePackets(buffer); // busy waits for packets

        pool -> joinQueue([this, buffer]() mutable 
            {
                packetHandler(buffer);
            }
        );
    }  
}