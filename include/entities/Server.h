#ifndef SERVER_H
#define SERVER_H 

#include "Entity.h"

// UDP Server Class
class Server : public Entity {
    private: 

        void initUDPSocket();
        void receive(); //non-blocking receive 
        

    public:
        Server(std::string socketAddress, int socketPort);
        ~Server();

        void listen();

};

#endif
