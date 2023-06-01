#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <boost/asio.hpp>

//#include "fileTransfer/FileTransfer.h"


// Base class for Server and Client
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

        // Accessors
        boost::asio::ip::udp::endpoint getEntityEndpoint();
        boost::asio::ip::udp::socket& getEntitySocket();

        // Mutators
        void openUDPSocket();
        void bindUDPSocket(); // Server only
        void closeSocket();

};

#endif
