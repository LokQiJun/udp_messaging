#ifndef ENTITY_H
#define ENTITY_h

//#include "fileTransfer/FileTransfer.h"
#include "vidStream/VidStream.h"

#include <string>
#include <boost/asio.hpp>


// abstract class
class Entity 
{

    protected:
        VidStream *vidStream;
        //FileTransfer *fileTranfer;
        
        std::string socketAddress;
        int socketPort;
        boost::asio::io_service ioService;
        boost::asio::ip::udp::endpoint endpoint;
        boost::asio::ip::udp::socket socket;

    public:
        // Constructor and Destructor
        Entity(std::string socketAddress, int socketPort);
        ~Entity();

        

        void openUDPSocket();
        void bindUDPSocket(); // Server only
        void closeSocket();

};

#endif
