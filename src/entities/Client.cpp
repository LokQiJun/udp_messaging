#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "entities/Client.h"
#include "utils.h"

Client::Client(std::string socketAddress, int socketPort) 
    : Entity(socketAddress, socketPort) 
{    
    std::cout << "Client assigned to " << socketAddress << ":" << socketPort << std::endl;
}

Client::~Client()
{
}

void Client::send_handler(std::vector<char> data_buf)
{
    Entity::openUDPSocket();
    boost::system::error_code err;

    std::cout << data_buf.data() << std::endl;
    
    if (PACKET_SIZE > data_buf.size())
    {
        data_buf.resize(PACKET_SIZE, '\x00');
    }
    
    socket.send_to(boost::asio::buffer(data_buf), Entity::endpoint, 0, err );
    if (err) 
    {
        std::cout << "Failed to send: " << err.message() << std::endl;
    }
    Entity::closeSocket();
    return;
}
