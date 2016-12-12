//
//  Queue.cpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 01.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#include "SerialQueue.hpp"
#include "QueuePool.hpp"

using namespace TinyDispatch;

void queueThreadLoop(Queue* q);

SerialQueue::SerialQueue(std::string identifier){}

Queue* SerialQueue::get(std::string identifier)
{
    Queue* q = QueuePool::getQueue(identifier);
    if (q != NULL)
    {
        return q;
    }
    q = new SerialQueue(identifier);
    QueuePool::setQueue(identifier,q);
    return q;
}

Queue* SerialQueue::global()
{
    return new SerialQueue("tmp");
}


void SerialQueue::async(Block b)
{
    access.lock();
    this->queue.push(b);
    this->commit();
    access.unlock();
}

void SerialQueue::sync(Block b)
{
    exec_access.lock();
    b();
    exec_access.unlock();
}

void SerialQueue::commit(void)
{
    if (this->thread == NULL)
    {
        this->thread = new std::thread(serialQueueThreadLoop,this);
        thread->detach();
    }
}

bool SerialQueue::isEmpty()
{
    bool result = true;
    access.lock();
    result = queue.empty();
    if(result)
    {
        if (thread != NULL)
        {
            delete thread;
            thread = NULL;
        }
    }
    access.unlock();
    return result;
}

void SerialQueue::serialQueueThreadLoop(SerialQueue* q)
{
    while (!q->isEmpty())
    {
        q->access.lock();
            Block b = q->queue.front();
            q->queue.pop();
        q->access.unlock();
        q->exec_access.lock();
            b();
        q->exec_access.unlock();
    }
}

/*
SerialQueue::~SerialQueue()
{
     queues.remove
}
*/
