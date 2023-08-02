#ifndef SENDER_H
#define SENDER_H 

#include "../entities/Client.h"

#include <string>

// Parent class for all Sender classes
class Sender 
{
    protected:
        Client* client;
    public:
        Sender(Client* client) : client(client) {}
        virtual ~Sender() {}

        virtual void send(std::string content) = 0;
        
};

#endif
