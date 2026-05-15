/*
Be able to:
Manager worker threads
Manage job queue
Coordinate execution lifestyle
*/

#include "../include/ThreadPool.hpp"
#include "../include/FileCopier.hpp"
#include <memory>

ThreadPool::ThreadPool(int numThreads) : numThreads(numThreads), stop(false)
{
    this->numThreads = numThreads;
}

ThreadPool::~ThreadPool() 
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }

    cv.notify_all();

    for(std::thread& t : workers)
    {
        if(t.joinable())
        {
            t.join();
        }
    }
}

void ThreadPool::addJob(const Job& job)
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        jobs.push(job);
    }
    cv.notify_one();
}

void ThreadPool::start()
{
    for(int i = 0; i < numThreads; i++)
    {
        workers.emplace_back(&ThreadPool::workerThread, this);
    }
}

void ThreadPool::wait()
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    cv.notify_all();
    for(std::thread& w: workers)
    {
        if(w.joinable())
        {
            w.join();
        }
    }
}

void ThreadPool::workerThread()
{
    auto fileCopy = std::make_unique<FileCopier>();

    while(true)
    {
        Job job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this](){
                return !jobs.empty() || stop;
            });
            if (stop && jobs.empty())
            {
                return;
            }

            job = jobs.front();
            jobs.pop();
        }
        fileCopy->copyFile(job.source, job.destination);
    }
}