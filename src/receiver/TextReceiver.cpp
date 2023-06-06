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
    boost::array<char,PACKET_SIZE> buffer;
    int bytesReceived = server -> receive(buffer);

    int numPacks = std::stoi(std::string(buffer.data(), bytesReceived));
    
    //Receive all data packets
    for (std::size_t i = 0; i < numPacks; i++)
    {
        buffer = {}; //clear buffer
        bytesReceived = server -> receive(buffer);
        std::cout << "Received [" << getCurrDatetimeStr() << "]" << buffer.data() << std::endl;
    }
}
