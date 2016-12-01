//
//  Queue.cpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 01.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#include "Queue.hpp"
#include <map>

using namespace TinyDispatch;

std::map<std::string,Queue*> queues;
void queueThreadLoop(Queue* q);

Queue::Queue(std::string identifier)
{
    queues[identifier] = this;
}

Queue* Queue::get(std::string identifier)
{
    Queue* q = queues[identifier];
    if (q != NULL)
    {
        return q;
    }
    return new Queue(identifier);
}

void Queue::async(Block b)
{
    access.lock();
    this->queue.push(b);
    this->commit();
    access.unlock();
}

void Queue::sync(Block b)
{
    exec_access.lock();
    b();
    exec_access.unlock();
}

void Queue::commit(void)
{
    if (this->thread == NULL)
    {
        this->thread = new std::thread(queueThreadLoop,this);
        thread->detach();
    }
}

bool Queue::isEmpty()
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

void Queue::queueThreadLoop(Queue* q)
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
Queue::~Queue()
{
     queues.remove
}
*/
