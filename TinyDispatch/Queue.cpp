//
//  Queue.cpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 12.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#include "Queue.hpp"
#include "SerialQueue.hpp"

using namespace TinyDispatch;

Queue* Queue::global()
{
    return SerialQueue::global();
}

Queue* Queue::get(std::string qid)
{
    return SerialQueue::get(qid);
}
