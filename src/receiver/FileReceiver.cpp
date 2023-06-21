#include "receiver/FileReceiver.h"
#include "UDPPacket/UDPPacket.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <map>

FileReceiver::FileReceiver(Server* server)
    : Receiver(server)
{
}

FileReceiver::~FileReceiver()
{
}

void FileReceiver::receive()
{
    // Stores packets in order (key: packetOrder, value: packet payload)
    std::map<int, std::vector<char>> receivedPackets;

    // Util variables for receiveing packet
    std::vector<char> buffer(PACKET_SIZE);
    int bytesReceived = 0;
    int numPacks = 0;
    std::string filetype = "";
   
    // Receive
    std::cout << "Receiving..." << std::endl;
    do 
    {
        // Receive Packets
        bytesReceived = server -> receive_handler(buffer);
        UDPHeader udpHeader = removeHeader(buffer);
        
        // Set number of packets to receive
        if (numPacks == 0) numPacks = udpHeader.numPackets;

        // Set filetype
        if (filetype.empty()) filetype = udpHeader.filetype;

        // Store packet payload in map
        receivedPackets[udpHeader.packetOrder] = buffer;
        std::cout << udpHeader.packetOrder << ", ";

        buffer.clear();
        buffer.resize(PACKET_SIZE);
    }   
    while (receivedPackets.size() < numPacks);

    //Create file
    std::cout << "Writing file..." << std::endl;
    std::string filepath = "storage/" + datetimeToFilename() + "." + filetype;
    std::ofstream outputfile(filepath, (std::ios::binary | std::ios::app));
    if (!outputfile.is_open())
    {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    for (const auto& pair: receivedPackets)
    {
        outputfile.write(pair.second.data(), pair.second.size());
    }

    outputfile.close();
    std::cout << "File received and stored as " << filepath << std::endl;
    return;
}

