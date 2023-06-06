#include "receiver/FileReceiver.h"

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
    boost::array<char,PACKET_SIZE> buffer;
    int bytesReceived = server -> receive(buffer);
    int numPacks;
    try
    {
        numPacks = std::stoi(std::string(buffer.data(), bytesReceived));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    std::cout << numPacks << std::endl;
    //Create file
    std::string filepath = "storage/" + datetimeToFilename() + ".mp4";
    std::ofstream outputfile(filepath, (std::ios::binary | std::ios::app));
    if (!outputfile.is_open())
    {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }
    
    for (std::size_t i = 0; i < numPacks; i++)
    {
        
        buffer = {}; //clear buffer
        bytesReceived = server -> receive(buffer);
        outputfile.write(buffer.data(), bytesReceived);
    }

    outputfile.close();
    std::cout << "File received and stored as " << filepath << std::endl;
    return;
}

