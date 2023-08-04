#include "concurrency/ThreadPool.h"

#include <thread>
#include <iostream>

ThreadPool::ThreadPool(int numThreads)
    : stopPool(false)
{
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back([this]{
            while (true)
            {
                std::function<void()> task;
                
                // Critical section (Tasks queue)
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
                // End of critical section (Tasks queue)
                task(); // runs task
            }
        });
    }
    std::cout << "ThreadPool with " << numThreads << " threads initialised." << std::endl;
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