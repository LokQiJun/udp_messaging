#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <mutex>
#include <vector>
#include <functional>
#include <condition_variable>

class ThreadPool
{
    private:
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;
        std::condition_variable queueCondition;
        std::mutex queueMutex;
        bool stopPool;
    
    public:
        ThreadPool(int numThreads);
        ~ThreadPool();

        template <typename F, typename ...Args>
        void joinQueue(F&& f, Args&&... args);
};

#endif