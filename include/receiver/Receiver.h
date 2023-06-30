#ifndef RECEIVER_H
#define RECEIVER_H

#include "utils.h"
#include "entities/Server.h"

#include <string>
#include <boost/array.hpp>

class Receiver
{
    protected:
        Server* server;
    public:
        Receiver(Server* server) : server(server) {}
        virtual ~Receiver() {}

        virtual void receive() = 0;
};

#endif