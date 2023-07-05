#include "receiver/MainReceiver.h"

#include "concurrency/ThreadPool.h"
#include "UDPPacket/UDPPacket.h"
#include "utils.h"

#include <fstream>
#include <future>
#include <iostream>
#include <functional>

void MainReceiver::packetHandler(std::vector<char>& buffer)
{
    //Extract data
    UDPHeader udpheader = removeHeader(buffer);
    std::map<int, std::vector<char>> completeMap;

    {
        std::lock_guard<std::mutex> lock(mapMutex); // Obtain mutex
        if (filenameDataMap.find(udpheader.filename) == filenameDataMap.end()) {
            filenameDataMap[udpheader.filename] = std::map<int, std::vector<char>>();
        }
        std::map<int, std::vector<char>>& dataMap = filenameDataMap[udpheader.filename];
        dataMap[udpheader.packetOrder] = buffer;
    
        if (dataMap.size() >= udpheader.numPackets)
        {
            completeMap = dataMap;
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