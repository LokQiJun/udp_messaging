#include "receiver/TextReceiver.h"
#include "UDPPacket/UDPPacket.h"
#include "utils.h"

#include <map>
#include <vector> 
#include <iostream>
#include <chrono>
#include <fstream>

TextReceiver::TextReceiver(Server* server)
    : Receiver(server)
{
}

TextReceiver::~TextReceiver()
{
}

void TextReceiver::receive()
{
    // Stores packets in order (key: packetOrder, value: packet payload)
    std::map<int, std::vector<char>> receivedPackets;

    // Util variables for receiveing packet
    std::vector<char> buffer(PACKET_SIZE);
    int bytesReceived = 0;
    int numPacks = 0;
    
    // Receive
    std::cout << "Receiving..." << std::endl;
    do 
    {
        // Receive Packets
        bytesReceived = server -> receivePackets(buffer);
        UDPHeader udpHeader = removeHeader(buffer);
        
        // Set number of packets to receive
        numPacks = udpHeader.numPackets;

        // Store packet payload in map
        receivedPackets[udpHeader.packetOrder] = buffer;

        buffer.clear();
        buffer.resize(PACKET_SIZE);
    }   
    while (receivedPackets.size() < numPacks);

    //Print message
    for (const auto& pair: receivedPackets)
    {
        std::cout << "\nPacket " << pair.first << ": " << std::string(pair.second.begin(), pair.second.end()) << std::endl;
    }
    std::cout << "Message Received." << std::endl;
}