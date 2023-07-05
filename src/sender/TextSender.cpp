#include "sender/TextSender.h"
#include "UDPPacket/UDPPacket.h"
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
    // Format custom header for UDP packet
    std::cout << content << std::endl;
    UDPHeader udpHeader = formatHeader("message.message", content.length());
    std::vector<char> buffer(PACKET_SIZE);
    
    // Send data 
    int packetCount = 0;
    std::size_t offset = 0;
    while (offset < content.size())
    {
        // Prepare buffer for next data packet
        buffer.clear();
        buffer.resize(PACKET_SIZE);
        
        // Attach header to UDP packet
        packetCount++;
        udpHeader.packetOrder = packetCount;
        int headerSize = attachHeader(udpHeader, buffer);
        
        // Calculate payload size
        std::size_t payloadSize = std::min(PACKET_SIZE, int(content.size() - offset));

        // Client sends buffer
        std::copy(content.begin() + offset, content.begin() + offset + payloadSize, buffer.begin() + headerSize + 1);
        client -> send_handler(buffer);
        
        // Update variables for next iteration
        offset += payloadSize;
        std::cout << "Progress: " << (static_cast<float>(offset)/content.size())*100 << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    
    std::cout << "Message sent." << std::endl;
    return;
}

