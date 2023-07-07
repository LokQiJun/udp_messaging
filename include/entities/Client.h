#ifndef CLIENT_H
#define CLIENT_H

#include "Entity.h"

#include <queue>
#include <vector>

// UDP Client Class

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
        bool queuePriority(std::vector<char>& buffer);
        bool queueNormal(std::vector<char>& buffer);

        void sendHandler(std::vector<char> data);
        void sendHandler();
};

#endif
