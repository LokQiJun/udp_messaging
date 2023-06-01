#ifndef SERVER_H
#define SERVER_H 

#include "Entity.h"
#include "utils.h"

// UDP Server Class
class Server : public Entity {
    private: 

        void initUDPSocket();
        void receive(); //non-blocking receive 
        int receive(boost::array<char, PACKET_SIZE>& buffer);
        

    public:
        Server(std::string socketAddress, int socketPort);
        ~Server();

        void listen();

};

#endif
