#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"

#include <queue>
#include <vector>

// UDP Client that sends UDP packets
class Client : public Entity 
{
    private:
        static Client* clientInstance;
        Client();
        ~Client();

        static int queueCapacity;
        std::queue<std::vector<char>> priorityQueue;
        std::queue<std::vector<char>> normalQueue;
 
 
    public:
        static Client* getInstance();  

        // Setter
        static void setQueueCapcity(int x);

        // Functions 
        void sendHandler(std::vector<char> data);

        // TODO: Implement new sending logic 
        bool queuePriority(std::vector<char>& buffer);
        bool queueNormal(std::vector<char>& buffer);

        void sendHandler();
};

#endif
