#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <boost/asio.hpp>

#define CLIENT_PORT 5000
#define SERVER_PORT 5005

// Parent class for Server and Client classes
class Entity 
{
    protected:
        std::string socketAddress;
        int socketPort;
        boost::asio::io_service ioService;
        boost::asio::ip::udp::endpoint endpoint;
        boost::asio::ip::udp::socket socket;

    public:
        // Constructor and Destructor
        Entity(std::string socketAddress, int socketPort);
        ~Entity();

        // Mutators
        void openUDPSocket();
        void bindUDPSocket(); // Server only
        void closeSocket();

};

#endif
