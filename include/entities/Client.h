#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"

// UDP Client Class
class Client : public Entity {
    private: 
        void send_handler(std::vector<char> data);
        
    public:
        Client(std::string socketAddress, int socketPort);
        ~Client();

        void send(std::string msg);
        void sendFile(std::string filepath);

};

#endif
