#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"


class Client : public Entity {
    public:
        Client(std::string socketAddress, int socketPort);
        ~Client();


};

#endif
