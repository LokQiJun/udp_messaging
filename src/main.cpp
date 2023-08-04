#include <iostream>

#include "utils.h"
#include "sender/TextSender.h"
#include "sender/FileSender.h"
#include "receiver/MainReceiver.h"
#include "concurrency/ThreadPool.h"
#include "streaming/VideoPlayer.h"
#include "streamUpload/VidStreamUpload.h"
#include "sender/SenderFactory.h"

#define CLIENT_PORT 5000
#define SERVER_PORT 5005

int main(int argc, char *argv[])
{

    auto senderInterface = []()
    {
        while (true)
        {
            std::string senderType;
            std::cout << "\nSender Type (message/file) or `quit`: ";
            std::getline(std::cin, senderType);
            if (strcmp(senderType.c_str(), "quit") == 0)
            {
                break;
            }

            SenderFactory senderFactory;
            Sender* sender = senderFactory.makeSender(senderType);

            if (sender)
            {
                std::thread senderThread([&sender, &senderType]() 
                {
                    std::cout << senderType << ": ";
                
                    std::string content;
                    std::getline(std::cin, content);
                    sender -> send(content);
                });

                senderThread.join();
            }
            else
            {
                std::cerr << "Invalid Sender Type" << std::endl;
            }
        }
    };



    auto receiverInterface = [](Server* server) {
        int numThreads = 5;
        MainReceiver mainReceiver(server, numThreads);
        mainReceiver.run();
    };
  
    
    if (argc < 2)
    {
        appUsage();
        return 0;
    }

    if (strcmp(argv[1], "-S") == 0)
    {
        // Initialise client singleton classes
        Client* client = Client::getInstance();
        std::thread senderInterfaceThread(senderInterface);
        std::thread clientSendThread([&client]()
        {
            client->sendHandler();
        });
        senderInterfaceThread.join();
        clientSendThread.join();
    }
    else if (strcmp(argv[1], "-R") == 0)
    {
        // Initialise server singleton classes
        Server* server = Server::getInstance();
        std::thread receiverThread(receiverInterface, server);

        VideoPlayer* videoPlayer = VideoPlayer::getInstance();
        videoPlayer -> playback();
        receiverThread.join(); // Receive frames 
    }
    else if (strcmp(argv[1], "-U") == 0)
    {
        Client* client = Client::getInstance();
        VidStreamUpload vidStreamUpload(client);

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
        Server* server = Server::getInstance();
        std::thread receiverThread(receiverInterface, server);
       
       
        VideoPlayer* videoPlayer = VideoPlayer::getInstance();
        videoPlayer -> playback();
        receiverThread.join(); // Receive frames  
    }
    
    return 0;
}
