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
    // TODO: manage socket connection more efficiently 
    // TODO: check limit for buffer size
    Entity::openUDPSocket();
    boost::system::error_code err;
    
    socket.send_to(boost::asio::buffer(data_buf), Entity::endpoint, 0, err );
    if (err) 
    {
        std::cout << "Failed to send: " << err.message() << std::endl;
    }
    Entity::closeSocket();
    return;
}
