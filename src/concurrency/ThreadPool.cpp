#include "concurrency/ThreadPool.h"

#include <thread>
#include <iostream>

ThreadPool::ThreadPool(int numThreads)
    : stopPool(false)
{
    for (int i = 0; i < numThreads; ++i)
    {
        std::cout << "Thread " << i << std::endl;
        threads.emplace_back([this]{
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    queueCondition.wait(lock, [this] {return (stopPool || !tasks.empty());}); // threads waits until first task appears
                    if (tasks.empty())
                    {
                        return; // destroys worker thread
                    }
                    task = tasks.front();
                    tasks.pop();
                }
                task(); // runs task
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queueMutex); // worker threads cannot enter critical section
        stopPool = true;
    }

    queueCondition.notify_all(); // notifies all waiting threads to wake and destroy themselves
    
    for (auto& thread : threads)
    {
        thread.join(); // wait for all threads to finish
    }
}