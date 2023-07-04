#ifndef MAINRECEIVER_H
#define MAINRECEIVER_H

#include "utils.h"
#include "entities/Server.h"
#include "concurrency/ThreadPool.h"

#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <iostream>
#include <boost/array.hpp>

class MainReceiver
{
    protected:
        Server* server;
        ThreadPool* pool;
        std::map<std::string, std::map<int, std::vector<char>>> filenameDataMap;
        std::mutex mapMutex;
    public:
        MainReceiver(Server* server, int numThreads)
            : server(server), pool(new ThreadPool(numThreads)){}
        ~MainReceiver(){}

        void packetHandler(std::vector<char>& buffer);
        void run();
};

#endif
