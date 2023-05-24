#include "entities/Server.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <boost/array.hpp>

// Constructor
Server::Server(std::string socketAddress, int socketPort) : Entity(socketAddress, socketPort) {
    initUDPSocket();
}

// Destructor
Server::~Server() {
}

// Private Functions
void Server::initUDPSocket(){
    Entity::openUDPSocket();
    Entity::bindUDPSocket();
} 

void Server::receive(){
    
    // read bytes from socket
    bool firstPacketRecieved = false;
    int numPacks;
    
    boost::asio::ip::udp::endpoint clientEndpoint;
    boost::array<char, 1024> recv_buffer;
    std::size_t bytesReceived = socket.receive_from(boost::asio::buffer(recv_buffer), clientEndpoint);

    // declare output file for receive operation
    // #TODO: implement file type agnostic file declaration
    std::ofstream outputFile = std::ofstream("storage/" + getCurrTime() + ".txt", std::ios::binary | std::ios::app);
    if(!outputFile.is_open()){
        std::cout << "Failed to write to output file" << std::endl;
        return;
    }

    if(!firstPacketRecieved) {
        //first packet to contain total number of packets sent
        try {
            std::string sVal = std::string(recv_buffer.begin(), recv_buffer.begin()+bytesReceived);
            numPacks = std::stoi(sVal);
        } catch( std::exception& e) {
            std::cout << "error reading lead packet, failed to read file" << std::endl;
            return;
        }
        
    } else {
        for (std::size_t i = 0; i < numPacks; i++){
            std::cout << "LOOPING" << std::endl;
            boost::system::error_code error;
            bytesReceived = socket.receive_from(boost::asio::buffer(recv_buffer), clientEndpoint, 0, error);
            
            if (error && error != boost::asio::error::message_size) {
                std::cout << "Failed to receive packet " << i << " (" << error.message() << ")" << std::endl;
                break;
            }
                            
            outputFile.write(recv_buffer.data(), bytesReceived);
        }
    }

}



// Public Functions
void Server::listen() {
    while (true){
        receive(); //Synchronous receive
    }
}


