#include "sender/TextSender.h"

TextSender::TextSender(Client* client)
    : Sender(client)
{
}

TextSender::~TextSender()
{
}

void send(std::string content)
{
    // Send metadata
    std::string numPacks = std::to_string(ceilDiv(msg.size(), PACKET_SIZE));
    std::vector<char> buffer(numPacks.begin(), numPacks.begin()+1); 
    client -> send_handler(buffer);
    
    // Send data 
    std::size_t offset = 0;
    while (offset < msg.size())
    {
        // Prepare buffer for next data packet
        buffer.clear();
        std::size_t length = std::min(PACKET_SIZE, int(msg.size() - offset));
        buffer.resize(length);
        buffer.shrink_to_fit();

        // Client sends buffer
        std::copy(msg.begin() + offset, msg.begin() + offset + length, buffer.begin());
        client -> send_handler(buffer);
        
        std::cout << "Progress: " << offset+length << "/" << msg.size() << std::endl;
        offset += length;
    }
    
    std::cout << "Message sent." << std::endl;
    return;
}

