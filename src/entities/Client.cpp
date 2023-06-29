#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "entities/Client.h"
#include "utils.h"

// Initialise singleton instance
Client* Client::clientInstance = nullptr;
// Default queue size
int Client::queueCapacity = 10; 

// Constructor 
Client::Client()
    : Entity("127.0.0.0", CLIENT_PORT) // localhost
{
    std::cout << "Client assigned to 127.0.0.0:" << socketPort << std::endl;
}

// Destructor
Client::~Client()
{
}

// Get singleton instance 
Client* Client::getInstance()
{
    if (clientInstance == NULL)
    {
        clientInstance = new Client();
    }
    return clientInstance;
}

void Client::setQueueCapcity(int x)
{
    queueCapacity = x;
}

bool Client::queuePriority(std::vector<char>& buffer)
{
    if (priorityQueue.size() < queueCapacity)
    {
        priorityQueue.push(buffer);
        return true;
    }
    else
    {
        return false;
    }
}

bool Client::queueNormal(std::vector<char>& buffer)
{
    if (normalQueue.size() < queueCapacity)
    {
        normalQueue.push(buffer);
        return true;
    }
    else
    {
        return false;
    }
}

// Send data packet (TODO: control rate of flow)
void Client::send_handler(std::vector<char> data_buf)
{   
    Entity::openUDPSocket();
    boost::system::error_code err;

    // std::cout << data_buf.data() << std::endl;
    
    if (PACKET_SIZE > data_buf.size())
    {
        data_buf.resize(PACKET_SIZE, '\x00');
    }
    
    socket.send_to(boost::asio::buffer(data_buf), Entity::endpoint, 0, err );
    if (err) 
    {
        std::cout << "Failed to send: " << err.message() << std::endl;
    }
    Entity::closeSocket();
    return;
}

void Client::send_handler()
{
    openUDPSocket(); 
    boost::system::error_code err;
    std::vector<char>* buffer_ptr = nullptr;

    int count = 0;
    while (priorityQueue.size() > 0 || normalQueue.size() > 0)
    {   
        /*
        Custom scheduling: 
        priority queue gets to send up to 10 packets per cycle, 
        normal queue gets to send up to 5 packets per cycle
        */
        if (count < 10 && priorityQueue.size() > 0)
        {
            buffer_ptr = &priorityQueue.front();
            priorityQueue.pop();
            count++;
        }
        else if (count < 15 && normalQueue.size() > 0)
        {
            buffer_ptr = &normalQueue.front();
            normalQueue.pop();
            count++;
        }
        else
        {
            count = 0;
        }

        // send when data is available for sending
        if (buffer_ptr != NULL)
        {
            // Fill buffer with null characters, up to size of packet
            if (PACKET_SIZE > (*buffer_ptr).size())
            {
                (*buffer_ptr).resize(PACKET_SIZE, '\x00');
            }
            
            // Send packet
            socket.send_to(boost::asio::buffer((*buffer_ptr)), endpoint, 0, err);
            if (err) 
            {
                std::cout << "Failed to send: " << err.message() << std::endl;
            }   
        }
    }
    
    closeSocket();
    return;
}