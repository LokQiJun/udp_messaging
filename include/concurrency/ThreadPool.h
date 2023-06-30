#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
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

        // template <typename F, typename ...Args>
        // void joinQueue(F&& f, Args&&... args)
        // {
        //     std::cout << "Joining lambda function to queue" << std::endl;
        //     std::unique_lock<std::mutex> lock(queueMutex); // obtain mutex to write to queue
        //     tasks.emplace([=] { std::__invoke(std::forward<F>(f), std::forward<Args>(args)...); });
        //     queueCondition.notify_one();
        //     std::cout << "Joined lambda function to queue, waiting for thread to run" << std::endl;
        // }
        
        
        template <typename F>
        void joinQueue(F f)
        {
            std::cout << "Joining lambda function to queue" << std::endl;
            std::unique_lock<std::mutex> lock(queueMutex); // obtain mutex to write to queue
            tasks.emplace(&f);
            queueCondition.notify_one();
            std::cout << "Joined lambda function to queue, waiting for thread to run" << std::endl;
        }
};

#endif