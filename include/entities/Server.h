#ifndef SERVER_H
#define SERVER_H 

#include "Entity.h"
#include "utils.h"

#include <vector>

// UDP Server Class
class Server : public Entity {
    private: 
        void initUDPSocket();     

    public:
        Server(std::string socketAddress, int socketPort);
        ~Server();

        int receive(boost::array<char, PACKET_SIZE>& buffer); // Text Message and Files
        int receive(boost::array<char, STREAM_SIZE>& buffer); // Video Stream
};

#endif
