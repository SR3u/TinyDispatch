//
//  ConcurrentQueue.hpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 12.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#ifndef ConcurrentQueue_hpp
#define ConcurrentQueue_hpp

#include "Queue.hpp"
#include "SerialQueue.hpp"
#include <vector>
#include <mutex>
namespace TinyDispatch
{
    class ConcurrentQueue : Queue
    {
    private:
        int currentQueue = 0;
        std::vector<Queue*> queues;
        std::mutex lock;
        ConcurrentQueue(std::string identifier, int concurrentThreads);
        ~ConcurrentQueue();
        virtual void sync(Block b, int i);
    public:
        static Queue* get(std::string identifier);
        static Queue* get(std::string identifier, int concurrentThreads);
        static Queue* global();
        static Queue* global(int concurrentThreads);
        
        virtual void async(Block b);
        virtual void sync(Block b);
        
        static int defaultConcurrentThreadsCount();
    };
}

#endif /* ConcurrentQueue_hpp */
