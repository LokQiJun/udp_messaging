#ifndef SERVER_H
#define SERVER_H 

#include "Entity.h"

class Server : public Entity {
    private: 
        boost::array <char, 1024> recv_buffer;
        bool firstPacketRecieved = false;

        void initUDPSocket();
        void receive(); //non-blocking receive 
        void receiveHandler(const boost::system::error_code& error, size_t bytesTransferred);
        

    public:
        Server(std::string socketAddress, int socketPort);
        ~Server();

        void listen();
};

#endif