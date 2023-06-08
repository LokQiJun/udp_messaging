#include "receiver/TextReceiver.h"

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
    //Accept lead packet with meta data
    std::vector<char> buffer(PACKET_SIZE);
    int bytesReceived = server -> receive_handler(buffer);

    int numPacks = std::stoi(std::string(buffer.data(), bytesReceived));
    
    //Receive all data packets
    for (std::size_t i = 0; i < numPacks; i++)
    {
        buffer.clear();
        buffer.resize(1024);
        bytesReceived = server -> receive_handler(buffer);
        std::cout << "Received [" << getCurrDatetimeStr() << "] " << buffer.data() << std::endl;
    }
    std::cout << "Message Received." << std::endl;
}
