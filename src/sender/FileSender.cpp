#include "sender/FileSender.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <chrono> 
#include <thread>

FileSender::FileSender(Client* client)
    : Sender(client)
{
}

FileSender::~FileSender()
{
}

void FileSender::send(std::string content)
{
    // Open file
    std::string filepath = content;
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    // Get filesize 
    file.seekg(0, file.end);
    int filesize = file.tellg();
    file.seekg(0, file.beg);

    //Send metadata
    std::string numPacks = std::to_string(ceilDiv(filesize, PACKET_SIZE));
    std::cout << "LENGTH: " << filesize << " , Num Packs: " << numPacks << std::endl;
    std::vector<char> buffer(numPacks.begin(), numPacks.begin() + sizeof(numPacks)); 
    client -> send_handler(buffer); 
    

    int read = 0; // Number of bytes read from file
    int count = 0; // Number of packets sent
    while (read < filesize)
    {
        // Allocate space for buffer
        buffer.clear();
        int length = std::min(PACKET_SIZE, filesize-read);
        buffer.resize(length);
        buffer.shrink_to_fit();

        file.read(buffer.data(), length);
        client -> send_handler(buffer);
        read += length;
        
        count +=1;
        std::cout << count << ", ";
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::cout << filepath << " sent." << std::endl;
    return;

}
