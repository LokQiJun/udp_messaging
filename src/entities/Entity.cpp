#include "entities/Entity.h"

using boost::asio::ip::udp;

Entity::Entity(std::string socketAddress, int socketPort) 
        : socketAddress(socketAddress), socketPort(socketPort),
        endpoint(boost::asio::ip::address::from_string(socketAddress), socketPort),
        socket(ioService)
{      
}

void Entity::openUDPSocket(){
        socket.open(udp::v4());
}

void Entity::bindUDPSocket(){
        socket.bind(endpoint);
}

void Entity::closeSocket(){
        socket.close();
}
