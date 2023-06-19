#include "receiver/FileReceiver.h"
#include "utils.h"

#include <iostream>
#include <fstream>

FileReceiver::FileReceiver(Server* server)
    : Receiver(server)
{
}

FileReceiver::~FileReceiver()
{
}

void FileReceiver::receive()
{
    //Accept lead packet with meta data
    std::vector<char> buffer(PACKET_SIZE);
    int bytesReceived = server -> receive_handler(buffer);
    if (strcmp(std::string(buffer.data(), bytesReceived).c_str(),flushBuffer)==0)
    {   
        buffer.clear();
        buffer.resize(PACKET_SIZE);
        bytesReceived = server -> receive_handler(buffer);   
    }
    if (buffer.data() == NULL)
    {
        std::cout << "Is NULL" << std::endl;
    }
    std::cout << buffer.data() << std::endl;
    int numPacks = std::stoi(std::string(buffer.data(), bytesReceived));
    std::cout << numPacks << std::endl;
   
    //Create file
    std::string filepath = "storage/" + datetimeToFilename() + ".jpeg";
    std::ofstream outputfile(filepath, (std::ios::binary | std::ios::app));
    if (!outputfile.is_open())
    {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }
    
    std::cout << "Receiving" << std::endl;
    for (std::size_t i = 0; i < numPacks; i++)
    {
        buffer.clear();
        buffer.resize(PACKET_SIZE);
        bytesReceived = server -> receive_handler(buffer);
        
        if (strcmp(std::string(buffer.data(), bytesReceived).c_str(),flushBuffer)!=0)
        {
            std::cout << i << ", ";
            outputfile.write(buffer.data(), bytesReceived);
        } 
        else
        {
            i--;
        }
        
    }

    outputfile.close();
    std::cout << "File received and stored as " << filepath << std::endl;
    return;
}

