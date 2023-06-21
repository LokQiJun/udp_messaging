#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"

// UDP Client Class
class Client : public Entity 
{
    private:
        static Client* clientInstance;
        Client();
        ~Client();
    public:
        Client(std::string socketAddress, int socketPort);
        static Client* getInstance();
        void send_handler(std::vector<char> data);
};

#endif
