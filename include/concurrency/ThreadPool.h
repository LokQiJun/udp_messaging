#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <future>
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
        
        template <typename F, typename... Args>
        void joinQueue(F&& f, Args&&... args)
        {
            std::cout << "Joining lambda function to queue" << std::endl;
            auto task = std::make_shared<std::packaged_task<void()>> (
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            // Critical section (Tasks queue)
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                if (stopPool)
                {
                    std::cerr << "ThreadPool stopped, unable to queue more tasks" << std::endl;
                    return;
                }
                tasks.emplace([task](){(*task)();}); // lambda function exexutes task when called
            }

            queueCondition.notify_one();
            std::cout << "Joined lambda function to queue, waiting for thread to run" << std::endl;
        }
};

#endif