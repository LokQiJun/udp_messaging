#include <iostream>
#include "entities/Server.h"
#include "entities/Client.h"

int main(){
    std::string socketAddress = "127.0.0.1";
    int socketPort = 5005;

    // Server server(socketAddress, socketPort);
    // server.listen();

    
    Client client(socketAddress, socketPort);
    std::string res = "";
    while (res != "q"){
        std::cout << "Enter your message ('q' to quit): ";
        std::getline(std::cin, res);
        client.send(res);
    }
    return 0;
}
