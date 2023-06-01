#include <iostream>
#include <fstream>
#include <boost/array.hpp>

#include "entities/Server.h"
#include "utils.h"

// Constructor
Server::Server(std::string socketAddress, int socketPort) : Entity(socketAddress, socketPort)
{
    initUDPSocket();
    std::cout << "Server started" << std::endl;
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

void Server::receive()
{
    
    // read bytes from socket
    int numPacks;
    
    boost::asio::ip::udp::endpoint clientEndpoint;
    boost::array<char, PACKET_SIZE> recv_buffer;
    std::size_t bytesReceived = socket.receive_from(boost::asio::buffer(recv_buffer), clientEndpoint);

    // declare output file for receive operation
    // #TODO: implement file type agnostic file declaration
    std::string filepath = "storage/" + getCurrTime() + ".mp4";
    std::ofstream outputFile(filepath, (std::ios::binary | std::ios::app));
    std::string sVal = std::string(recv_buffer.data(), bytesReceived);
      
    if (!outputFile.is_open())
    {
        std::cout << "Failed to open file" << std::endl;
        return;
    }
   
    //first packet to contain total number of packets sent
    try 
    {
        numPacks = std::stoi(sVal);
        std::cout << numPacks << std::endl;
    } 
    catch (std::exception& e) 
    {
        //std::cout << "error reading lead packet, failed to read file" << std::endl;
        return;
    }
        
    for (std::size_t i = 0; i < numPacks; i++)
    {
        boost::system::error_code error;
        
        recv_buffer = {};
        bytesReceived = socket.receive_from(boost::asio::buffer(recv_buffer), clientEndpoint, 0, error);
        
        if (error && error != boost::asio::error::message_size) 
        {
            std::cout << "Failed to receive packet " << i << " (" << error.message() << ")" << std::endl;
            break;
        }
        //std::cout <<"\n" << i << "\n" << recv_buffer.data() << std::endl;
        outputFile.write(recv_buffer.data(), bytesReceived);
    }

    
    outputFile.close();
    std::cout << "File recieved and stored as " << filepath << std::endl;
    return;
}

// int Server::receive(boost::array<char, PACKET_SIZE>& buffer)
// {
//     boost::asio::ip::udp::endpoint clientEndpoint;
//     boost::system::error_code error;
//     int bytesReceived =  socket.receive_from(boost::asio::buffer(buffer), clientEndpoint, 0, error);
//     if (error)
//     {
//         std::cerr <<"Failed to receive packed" << std::endl;
//         return;
//     }
//     return bytesReceived;
// }

// Public Functions
void Server::listen() 
{
    while (true)
    {
        receive(); //Synchronous receive
    }
}
