#include "entities/Server.h"
#include "utils.h"

#include <iostream>
#include <fstream>

// Constructor
Server::Server(std::string socketAddress, int socketPort) : Entity(socketAddress, socketPort) {
    initUDPSocket();
}

// Destructor
Server::~Server() {
    Entity::closeSocket();
}

// Private Functions
void Server::initUDPSocket(){
    Entity::openUDPSocket();
    Entity::bindUDPSocket();
} 

void Server::receive(){
    
    // declare output file for receive operation
    // #TODO: implement file type agnostic file declaration
    std::ofstream outputFile = std::ofstream(getCurrTime()+".txt", std::ios::binary | std::ios::app);
    if(!outputFile.is_open()){
        std::cout << "Failed to write to output file" << std::endl;
        return;
    }

    // read bytes from socket
    
    int numPacks;
    boost::asio::ip::udp::endpoint clientEndpoint;
    std::size_t bytesReceived = socket.receive_from(boost::asio::buffer(recv_buffer), clientEndpoint);
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


