//
//  DispatchQueuePool.cpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 12.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#include "QueuePool.hpp"
#include <mutex>
#include <map>
using namespace TinyDispatch;

std::mutex lock;
std::map<std::string,Queue*> queues;

Queue* QueuePool::getQueue(std::string qid)
{
    lock.lock();
    Queue* q = queues[qid];
    lock.unlock();
    return q;
}

void QueuePool::setQueue(std::string qid, Queue* q)
{
    lock.lock();
    queues[qid] = q;
    lock.unlock();
}

