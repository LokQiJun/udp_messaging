#include "entities/Client.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <fstream>

Client::Client(std::string socketAddress, int socketPort) 
    : Entity(socketAddress, socketPort) 
{
}

void Client::send_handler(std::vector<char> data_buf){
    Entity::openUDPSocket();
    boost::asio::ip::udp::socket& socket = Entity::getEntitySocket();
    boost::asio::ip::udp::endpoint endpoint = Entity::getEntityEndpoint();
    boost::system::error_code err;
    
    socket.send_to(boost::asio::buffer(data_buf), Entity::endpoint, 0, err );
    if (err) {
        std::cout << "Failed to send: " << err.message() << std::endl;
    }
    Entity::closeSocket();
    return;
}

void Client::send(std::string msg){
    std::size_t offset = 0;
    std::vector<char> buffer(PACKET_SIZE);

    while (offset < msg.size()) {
        std::size_t length = std::min(PACKET_SIZE, int(msg.size() - offset));

        // copy string into buffer, up till max buffer size
        std::copy(msg.begin() + offset, msg.begin() + offset + length, buffer.begin());

        // fill buffer if there is empty space
        if (length < PACKET_SIZE) {
            std::fill(buffer.begin() + length, buffer.end(), '\0');
        }
        // Process the buffer
        send_handler(buffer);

        offset += length;
    }
    
    std::cout << "Message sent." << std::endl;

    return;
}

void Client::sendFile(std::string filepath){

    // open file
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    // send packets 
    // TODO: Check for number of packets and send as first pack
    std::vector<char> buffer(PACKET_SIZE);
    while (file.read(buffer.data(), PACKET_SIZE)) {
        send_handler(buffer);
    }

    std::cout << "File sent." << std::endl;
    return;
}
