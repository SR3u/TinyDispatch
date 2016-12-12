//
//  DispatchQueuePool.hpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 12.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#ifndef DispatchQueuePool_hpp
#define DispatchQueuePool_hpp

#include <string>
#include "Queue.hpp"
namespace TinyDispatch
{
    class QueuePool
    {
    public:
        static Queue* getQueue(std::string qid);
        static void setQueue(std::string qid, Queue* q);
    };
}

#endif /* DispatchQueuePool_hpp */
