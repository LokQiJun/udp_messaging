#include "sender/FileSender.h"
#include "UDPPacket/UDPPacket.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <chrono> 
#include <thread>

FileSender::FileSender(Client* client)
    : Sender(client)
{
}

FileSender::~FileSender()
{
}

void FileSender::send(std::string content)
{
    // Open file
    std::string filepath = content;
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    // Get filesize 
    file.seekg(0, file.end);
    int filesize = file.tellg();
    file.seekg(0, file.beg);

    // Format custom header for UDP packet
    UDPHeader udpHeader = formatHeader(filepath, filesize);
    std::vector<char> buffer(PACKET_SIZE);
    

    int packetCount = 0; // Number of packets sent
    int read = 0; // Number of bytes read from file
    while (read < filesize)
    {
        // Prepare buffer for next data packet
        buffer.clear();
        buffer.resize(PACKET_SIZE);

        // Attach header to UDP packet
        packetCount++;
        udpHeader.packetOrder = packetCount;
        int headerSize = attachHeader(udpHeader, buffer);

        // Calculate payload size
        std::size_t payloadSize = std::min(PACKET_SIZE-headerSize, filesize-read); // payload size corresponds to amount of space left in a packet or the amount of data left in a file

        // Client sends buffer
        if (packetCount%100==0)
        {
            std::cout << packetCount << ", ";
        }
        file.read(buffer.data() + headerSize, payloadSize);
        client -> sendHandler(buffer);
        
        // Update variables for next iteration
        read += payloadSize;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << filepath << " sent with " << packetCount << " packets." << std::endl;
    return;

}
