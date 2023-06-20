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
    // Send metadata
    // std::string numPacks = std::to_string(ceilDiv(content.size(), PACKET_SIZE));
    // std::vector<char> buffer(numPacks.begin(), numPacks.begin()+1); 
    
    // client -> send_handler(buffer);
    UDPHeader udpHeader = formatHeader("message", "message", content.length());
    std::vector<char> buffer(PACKET_SIZE);
    
    // std::vector<char> test(1000);
    // std::string hello = "hello";
    // memcpy(&test, &hello, hello.length());
    // std::cout << test.data() << std::endl;
    
    // Send data 
    int packet_count = 0;
    std::size_t offset = 0;
    while (offset < content.size())
    {

        // Prepare buffer for next data packet
        buffer.clear();
        // buffer.resize(length);
        // buffer.shrink_to_fit();
        buffer.resize(PACKET_SIZE);

        std::cout << "UDP Header: " << udpHeader.filename << std::endl;
        std::cout << "UDP Header: " << udpHeader.filetype << std::endl;
        std::cout << "UDP Header: " << udpHeader.numPackets << std::endl;
        std::cout << "UDP Header: " << udpHeader.packetOrder << std::endl;
        // Attach header to UDP packet
        packet_count++;
        udpHeader.packetOrder = packet_count;
        int headerSize = attachHeader(udpHeader, buffer);
        
        std::cout << buffer.data() << std::endl;
        // Calculate payload size
        std::size_t payloadSize = std::min(PACKET_SIZE, int(content.size() - offset));

        // Client sends buffer
        std::copy(content.begin() + offset, content.begin() + offset + payloadSize, buffer.begin() + headerSize + 1);
        std::cout << buffer.data() << std::endl;
        client -> send_handler(buffer);
        
        std::cout << "Progress: " << ((offset + payloadSize)/content.size())*100 << "%" << std::endl;
        offset += payloadSize;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::cout << "Message sent." << std::endl;
    return;
}

