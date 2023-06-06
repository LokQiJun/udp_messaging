#include <iostream>

#include "sender/TextSender.h"
#include "sender/FileSender.h"
#include "receiver/TextReceiver.h"
#include "receiver/FileReceiver.h"
#include "streamDownload/VidStreamDownload.h"
#include "streamUpload/VidStreamUpload.h"

int main(int argc, char *argv[])
{

    std::string socketAddress = "127.0.0.1";
    int socketPort = 5006;

    if (argc < 2)
    {
        appUsage();
        return 0;
    }

    if (strcmp(argv[1], "-TS") == 0)
    {
        Client* fileSendClient = new Client(socketAddress, socketPort);
        TextSender textSender(fileSendClient);
        
        std::string text;  
        while (true)
        {
            std::cout << "Enter message ('q' to quit): ";
            std::getline(std::cin, text);
            
            if (text == "q") break;
            else textSender.send(text);
        }   

    }
    else if (strcmp(argv[1], "-TR") == 0)
    {
        Server* textRecieveServer = new Server(socketAddress, socketPort);
        TextReceiver textReceiver(textRecieveServer);
        textReceiver.receive();

    }
    else if (strcmp(argv[1], "-FS") == 0)
    {
        Client* fileSendClient = new Client(socketAddress, socketPort);
        FileSender fileSender(fileSendClient);
        
        std::string filepath;  
        while (true)
        {
            std::cout << "Enter message ('q' to quit): ";
            std::getline(std::cin, filepath);
            
            if (filepath == "q") break;
            else fileSender.send(filepath);
        }   
    }
    else if (strcmp(argv[1], "-FR") == 0)
    {
        Server* fileRecieveServer = new Server(socketAddress, socketPort);
        FileReceiver fileReceiver(fileRecieveServer);
        fileReceiver.receive();

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
        appUsage();
    }

    return 0;
}
