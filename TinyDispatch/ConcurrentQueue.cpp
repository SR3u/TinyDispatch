//
//  ConcurrentQueue.cpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 12.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#include "ConcurrentQueue.hpp"
#include "QueuePool.hpp"
using namespace TinyDispatch;

ConcurrentQueue::ConcurrentQueue(std::string identifier, int concurrentThreads)
{
    lock.lock();
    for(int i = 0; i<concurrentThreads;i++)
    {
        queues.push_back(SerialQueue::global());
    }
    lock.unlock();
}
ConcurrentQueue::~ConcurrentQueue()
{
    lock.lock();
    for(int i = 0; i<queues.size();i++)
    {
        delete queues[i];
    }
    lock.unlock();
}

Queue* ConcurrentQueue::get(std::string identifier)
{
    return get(identifier,defaultConcurrentThreadsCount());
}
Queue* ConcurrentQueue::get(std::string identifier, int concurrentThreads)
{
    Queue* q = QueuePool::getQueue(identifier);
    if (q != NULL)
    {
        return q;
    }
    q = new ConcurrentQueue(identifier,concurrentThreads);
    QueuePool::setQueue(identifier,q);
    return q;
}
Queue* ConcurrentQueue::global()
{
    return global(defaultConcurrentThreadsCount());
}
Queue* ConcurrentQueue::global(int concurrentThreads)
{
    return new ConcurrentQueue("tmp",concurrentThreads);
}

void ConcurrentQueue::async(Block b)
{
    lock.lock();
    queues[currentQueue]->async(b);
    currentQueue = (currentQueue+1) % queues.size();
    lock.unlock();
}
void ConcurrentQueue::sync(Block b)
{
    lock.lock();
    sync(b,0);
    lock.unlock();
}

void ConcurrentQueue::sync(Block b, int i)
{
    if(i < queues.size())
    {
        queues[i]->sync([b,i,this](){
            this->sync(b, i+1);
        });
    }
    else
    {
        b();
    }
}

int ConcurrentQueue::defaultConcurrentThreadsCount()
{
    int t = std::thread::hardware_concurrency();
    return t > 1 ? t : 2;
}
