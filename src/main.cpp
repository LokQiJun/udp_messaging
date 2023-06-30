#include <iostream>

#include "utils.h"
#include "sender/TextSender.h"
#include "sender/FileSender.h"
#include "receiver/TextReceiver.h"
#include "receiver/FileReceiver.h"
#include "receiver/MainReceiver.h"
#include "concurrency/ThreadPool.h"
#include "streamDownload/VidStreamDownload.h"
#include "streamUpload/VidStreamUpload.h"
#include "sender/SenderFactory.h"

int main(int argc, char *argv[])
{

    std::string socketAddress = "127.0.0.1";
    int socketPort = 5006;
    int senderPort = 5005;
    int receiverPort = 5005;

    // Initialise server and client singleton classes
    Server* server = Server::getInstance();
    Client* client = Client::getInstance();

    // auto senderInterface = []()
    // {
    //     while (true)
    //     {
    //         std::string senderType;
    //         std::cout << "Sender Type (message/file) or `quit`: ";
    //         std::cin >> senderType;
    //         if (strcmp(senderType.c_str(), "quit"))
    //         {
    //             break;
    //         }

    //         SenderFactory senderFactory;
    //         Sender* sender = senderFactory.makeSender(senderType);

    //         if (sender)
    //         {
    //             std::thread senderThread([&sender, &senderType]() 
    //             {
    //                 std::cout << senderType << ": ";
                
    //                 std::string content;
    //                 std::cin >> content;
    //                 sender -> send(content);
    //             });

    //             senderThread.join();
    //         }
    //         else
    //         {
    //             std::cerr << "Invalid Sender Type" << std::endl;
    //         }
    //     }
    // };



    auto receiverInterface = [](Server* server) {
        int numThreads = 10;
        std::cout << "In receiver interface." << std::endl;
        MainReceiver mainReceiver(server, numThreads);
        mainReceiver.run();
    };
    std::thread receiverThread(receiverInterface, server);
    receiverThread.join();
    
    // if (argc < 2)
    // {
    //     appUsage();
    //     return 0;
    // }

    // if (strcmp(argv[1], "-S") == 0)
    // {
    //     std::thread senderInterfaceThread(senderInterface);
    //     std::thread clientSendThread([&client]()
    //     {
    //         client->send_handler();
    //     });
    //     senderInterfaceThread.join();
    //     clientSendThread.join();
    // }
    // else if (strcmp(argv[1], "-R") == 0)
    // {
    //     std::thread(receiverInterface);
    //     receiverInterface.join();
    // }   

    // if (argc < 2)
    // {
    //     appUsage();
    //     return 0;
    // }

    // if (strcmp(argv[1], "-TS") == 0)
    // {
    //     // Client* textSendClient = new Client(socketAddress, senderPort);
    //     // TextSender textSender(textSendClient);
    //     TextSender textSender(client);
        
    //     std::string text;  
    //     while (true)
    //     {
    //         std::cout << "Enter message ('q' to quit): ";
    //         std::getline(std::cin, text);
            
    //         if (text == "q") break;
    //         else 
    //         {
    //             textSender.send(text);
    //         }   
    //     }

    // }
    // else if (strcmp(argv[1], "-TR") == 0)
    // {
    //     // Server* textRecieveServer = new Server(socketAddress, receiverPort);
    //     // TextReceiver textReceiver(textRecieveServer);
    //     TextReceiver textReceiver(server);
    //     textReceiver.receive();

    // }
    // else if (strcmp(argv[1], "-FS") == 0)
    // {
    //     // Client* fileSendClient = new Client(socketAddress, senderPort);
    //     // FileSender fileSender(fileSendClient);
    //     // TextSender textSender(fileSendClient);
    //     FileSender fileSender(client);
        
    //     std::string filepath;  
    //     while (true)
    //     {
    //         std::cout << "Enter message ('q' to quit): ";
    //         std::getline(std::cin, filepath);
            
    //         if (filepath == "q") break;
    //         else 
    //         {
    //             fileSender.send(filepath);
    //         }
    //     }   
        
    // }
    // else if (strcmp(argv[1], "-FR") == 0)
    // {
    //     // Server* fileRecieveServer = new Server(socketAddress, receiverPort);
    //     // FileReceiver fileReceiver(fileRecieveServer);
    //     FileReceiver fileReceiver(server);
    //     fileReceiver.receive();

    // }
    // else if (strcmp(argv[1], "-U") == 0)
    // {
    //     // Client* streamClient = new Client(socketAddress, socketPort);
    //     // VidStreamUpload vidStreamUpload(streamClient);
    //     VidStreamUpload vidStreamUpload(client);
    
    //     std::string filepath = "";  
    //     while (true)
    //     {
    //         std::cout << "Enter filepath ('q' to quit): ";
    //         std::getline(std::cin, filepath);
            
    //         if (filepath == "q") break;
    //         else vidStreamUpload.upload(filepath);
    //     }   
    // }
    // else if (strcmp(argv[1], "-D") == 0)
    // {
    //     // Server* streamServer = new Server(socketAddress, socketPort);
    //     // VidStreamDownload vidStreamDownload(streamServer);
    //     VidStreamDownload vidStreamDownload(server);
    //     vidStreamDownload.download();
    // }
    // else 
    // {
    //     appUsage();
    // }

    return 0;
}
