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
    int bytesReceived = socket.receive_from(boost::asio::buffer(buffer), clientEndpoint);
    
    if (error && error != boost::asio::error::message_size) 
    {
        std::cerr << "Server failed to receive packet: " << error.message() << std::endl;
    }
  
    return bytesReceived;
}

int Server::receive_handler(boost::array<char, PACKET_SIZE>& buffer)
{
    boost::asio::ip::udp::endpoint clientEndpoint;
    boost::system::error_code error;
    int bytesReceived = socket.receive_from(boost::asio::buffer(buffer), clientEndpoint, 0, error);
    
    if (error && error != boost::asio::error::message_size) 
    {
        std::cerr << "Server failed to receive packet: " << error.message() << std::endl;
    }
    
    return bytesReceived;
}

int Server::receive_handler(boost::array<char, STREAM_SIZE>& buffer)
{
    boost::asio::ip::udp::endpoint clientEndpoint;
    boost::system::error_code error;
    int bytesReceived = socket.receive_from(boost::asio::buffer(buffer), clientEndpoint, 0, error);
    
    if (error && error != boost::asio::error::message_size) 
    {
        std::cerr << "Server failed to receive packet: " << error.message() << std::endl;
    }
    
    return bytesReceived;
}


