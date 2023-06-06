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

    std::string numPacks = std::to_string(ceilDiv(msg.size(), PACKET_SIZE));
    std::vector<char> buffer(numPacks.begin(), numPacks.begin()+1); 
    send_handler(buffer);
    
    while (offset < msg.size())
    {
        buffer.clear();

        std::size_t length = std::min(PACKET_SIZE, int(msg.size() - offset));
        std::cout << "LENGTH: " << length << "; msg.size(): " << msg.size() << "; offset: " << offset << std::endl;
        buffer.resize(length);
        buffer.shrink_to_fit();

        std::copy(msg.begin() + offset, msg.begin() + offset + length, buffer.begin());
        send_handler(buffer);

        offset += length;
    }
    // send_handler(std::vector<char>(0));// send b'' over to terminate
    std::cout << "Message sent." << std::endl;

    return;
}

void Client::sendFile(std::string filepath)
{
    // Open file
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    // file size 
    file.seekg(0, file.end);
    int filesize = file.tellg();
    file.seekg(0, file.beg);

    std::string numPacks = std::to_string(ceilDiv(filesize, PACKET_SIZE));
    std::cout << "LENGTH: " << filesize << " , Num Packs: " << numPacks << std::endl;
    std::vector<char> buffer(numPacks.begin(), numPacks.begin()+sizeof(numPacks)); 
    send_handler(buffer);

    int read = 0;
    int count = 0;
    while (read < filesize)
    {
        buffer.clear();
        int length = std::min(PACKET_SIZE, filesize-read);
        buffer.resize(length);
        buffer.shrink_to_fit();

        // std::copy(file.beg+read, file.beg+read+length, buffer.begin());
        file.read(buffer.data(), length);
        send_handler(buffer);
        read += length;
        //std::cout << read << " chars sent" << std::endl;
        count +=1;
        std::cout << count << ", ";
    }

    std::cout << "File sent." << std::endl;
    return;
}
