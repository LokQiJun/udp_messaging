#include "entities/Client.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <fstream>

Client::Client(std::string socketAddress, int socketPort) 
    : Entity(socketAddress, socketPort) 
{    
    std::cout << "Client started" << std::endl;
}

Client::~Client()
{
}

void Client::send_handler(std::vector<char> data_buf)
{
    Entity::openUDPSocket();
    boost::asio::ip::udp::socket& socket = Entity::getEntitySocket();
    boost::asio::ip::udp::endpoint endpoint = Entity::getEntityEndpoint();
    boost::system::error_code err;
    
    socket.send_to(boost::asio::buffer(data_buf), Entity::endpoint, 0, err );
    if (err) 
    {
        std::cout << "Failed to send: " << err.message() << std::endl;
    }
    Entity::closeSocket();
    return;
}

void Client::send(std::string msg)
{
    std::size_t offset = 0;
    
    while (offset < msg.size())
    {
        std::size_t length = std::min(PACKET_SIZE, int(msg.size() - offset));
        std::vector<char> buffer(length);

        // copy string into buffer
        std::copy(msg.begin() + offset, msg.begin() + offset + length, buffer.begin());
        send_handler(buffer);

        offset += length;
    }
    send_handler(std::vector<char>(0));// send b'' over to terminate
    std::cout << "Message sent." << std::endl;

    return;
}

void Client::sendFile(std::string filepath)
{

    // open file
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    // send packets 
    // TODO: Check for number of packets and send as first pack + create buffer based on available data
    std::vector<char> buffer(PACKET_SIZE);
    while (file.read(buffer.data(), PACKET_SIZE)) 
    {
        send_handler(buffer);
    }

    std::cout << "File sent." << std::endl;
    return;
}
