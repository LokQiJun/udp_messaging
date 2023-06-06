#include <iostream>

#include "entities/Server.h"
#include "entities/Client.h"
#include "streamDownload/VidStreamDownload.h"
#include "streamUpload/VidStreamUpload.h"

int main(int argc, char *argv[])
{

    std::string socketAddress = "127.0.0.1";
    int socketPort = 5005;


    if (strcmp(argv[1], "-S") == 0 )
    {
        Server server(socketAddress, socketPort);
        server.listen();

    } 
    else if (strcmp(argv[1], "-C") == 0)
    {
        
        Client client(socketAddress, socketPort);
        std::string res = "";

        while (true)
        {
            std::cout << "Enter filepath ('q' to quit): ";
            std::getline(std::cin, res);
            
            if (res == "q") break;
            else client.sendFile(res);
        }   
    }
    else if (strcmp(argv[1], "-U") == 0)
    {
        Client* streamClient = new Client(socketAddress, socketPort);
        VidStreamUpload vidStreamUpload(streamClient);
    
        std::string filepath = "";  
        while (true)
        {
            std::cout << "Enter filepath ('q' to quit): ";
            std::getline(std::cin, filepath);
            
            if (filepath == "q") break;
            else vidStreamUpload.upload(filepath);
        }   
    }
    else if (strcmp(argv[1], "-D") == 0)
    {
        Server* streamServer = new Server(socketAddress, socketPort);
        VidStreamDownload vidStreamDownload(streamServer);
        vidStreamDownload.download();
    }
    else 
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "-C : Client mode" << std::endl;
        std::cout << "-S : Server mode" << std::endl;
        std::cout << "-U : Stream upload mode " << std::endl;
        std::cout << "-D : Stream download mode " << std::endl;
    }


    
    return 0;
}
