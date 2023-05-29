#include <iostream>

#include "entities/Server.h"
#include "entities/Client.h"

int main(int argc, char *argv[])
{

    std::string socketAddress = "127.0.0.1";
    int socketPort = 5005;

    for (int i = 0; i < argc; i ++)
    {
        if (strcmp(argv[i], "-S") == 0 )
        {
            Server server(socketAddress, socketPort);
            server.listen();

        } 
        else if (strcmp(argv[i], "-C") == 0)
        {
           
            Client client(socketAddress, socketPort);
            std::string res = "";

            while (true)
            {
                // std::cout << "Enter your message ('q' to quit): ";
                // std::getline(std::cin, res);
                
                // if (res == "q") break;
                // else client.send(res);

                std::cout << "Enter filepath ('q' to quit): ";
                std::getline(std::cin, res);
                
                if (res == "q") break;
                else client.sendFile(res);
            }   
        }
    }
    return 0;
}
