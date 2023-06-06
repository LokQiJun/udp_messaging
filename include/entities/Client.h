#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"

// UDP Client Class
class Client : public Entity {
        
    public:
        Client(std::string socketAddress, int socketPort);
        ~Client();

        void send_handler(std::vector<char> data);
};

#endif
