#ifndef SERVER_H
#define SERVER_H 

#include "Entity.h"
#include "utils.h"
#include "../concurrency/ThreadPool.h"

#include <vector>

// UDP Server that receives UDP Packets
class Server : public Entity 
{
    private: 
        static Server* serverInstance;     
        
        Server();
        ~Server();
        
        void initUDPSocket();

    public:
        static Server* getInstance();
        
        int receivePackets(std::vector<char>& buffer);
};

#endif
