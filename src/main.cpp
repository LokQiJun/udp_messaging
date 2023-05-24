#include <iostream>
#include "entities/Server.h"
#include "entities/Client.h"

int main(){
    std::string socketAddress = "127.0.0.1";
    int socketPort = 5000;
    Server server(socketAddress, socketPort);

    server.listen();
    return 0;
}