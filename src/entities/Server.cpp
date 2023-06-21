#include "entities/Server.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <boost/array.hpp>
// Constructor
Server::Server(std::string socketAddress, int socketPort) : Entity(socketAddress, socketPort)
{
    initUDPSocket();
    std::cout << "Server started at " << socketAddress << ":" << socketPort << std::endl;
}

// Destructor
Server::~Server()
{
    Entity::closeSocket();
}

// Private Functions
void Server::initUDPSocket()
{
    Entity::openUDPSocket();
    Entity::bindUDPSocket();
} 

int Server::receive_handler(std::vector<char>& buffer)
{   
    
    boost::asio::ip::udp::endpoint clientEndpoint;
    boost::system::error_code error;
    int bytesReceived = 0;
    
    // Busy wait until we receive a packet with data
    do 
    {
        bytesReceived = socket.receive_from(boost::asio::buffer(buffer), clientEndpoint);
    }
    while (buffer.size() == PACKET_SIZE && std::all_of(buffer.begin(), buffer.end(), [](char c) { return c == '\x00'; }));


    // remove trailing null chars
    while (!buffer.empty() && buffer.back() == '\x00')
    {
        buffer.pop_back();
        bytesReceived--;
    }
    //std::cout << buffer.data() << std::endl;
    // if (error && error != boost::asio::error::message_size) 
    // {
    //     std::cerr << "Server failed to receive packet: " << error.message() << std::endl;
    // }
  
    return bytesReceived;
}

// int Server::receive_handler(boost::array<char, PACKET_SIZE>& buffer)
// {
//     boost::asio::ip::udp::endpoint clientEndpoint;
//     boost::system::error_code error;
//     int bytesReceived = socket.receive_from(boost::asio::buffer(buffer), clientEndpoint, 0, error);
    
//     if (error && error != boost::asio::error::message_size) 
//     {
//         std::cerr << "Server failed to receive packet: " << error.message() << std::endl;
//     }
    
//     return bytesReceived;
// }

// int Server::receive_handler(boost::array<char, STREAM_SIZE>& buffer)
// {
//     boost::asio::ip::udp::endpoint clientEndpoint;
//     boost::system::error_code error;
//     int bytesReceived = socket.receive_from(boost::asio::buffer(buffer), clientEndpoint, 0, error);
    
//     if (error && error != boost::asio::error::message_size) 
//     {
//         std::cerr << "Server failed to receive packet: " << error.message() << std::endl;
//     }
    
//     return bytesReceived;
// }


