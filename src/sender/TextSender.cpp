#include "sender/TextSender.h"
#include "utils.h"

#include <iostream>
#include <chrono>
#include <thread>

TextSender::TextSender(Client* client)
    : Sender(client)
{
}

TextSender::~TextSender()
{
}

void TextSender::send(std::string content)
{
    // Send metadata
    std::string numPacks = std::to_string(ceilDiv(content.size(), PACKET_SIZE));
    std::vector<char> buffer(numPacks.begin(), numPacks.begin()+1); 
    
    client -> send_handler(buffer);
    
    // Send data 
    std::size_t offset = 0;
    while (offset < content.size())
    {
        // Prepare buffer for next data packet
        buffer.clear();
        std::size_t length = std::min(PACKET_SIZE, int(content.size() - offset));
        buffer.resize(length);
        buffer.shrink_to_fit();

        // Client sends buffer
        std::copy(content.begin() + offset, content.begin() + offset + length, buffer.begin());
        client -> send_handler(buffer);
        
        std::cout << "Progress: " << ((offset+length)/content.size())*100 << "%" << std::endl;
        offset += length;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::cout << "Message sent." << std::endl;
    return;
}

