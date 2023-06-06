#ifndef SENDER_H
#define SENDER_H 

#include "../entities/Client.h"

#include <string>

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
