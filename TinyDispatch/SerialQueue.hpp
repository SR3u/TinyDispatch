//
//  SerialQueue.hpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 01.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#ifndef SerialQueue_hpp
#define SerialQueue_hpp

#include <mutex>
#include <string>
#include <queue>

#include "Queue.hpp"

namespace TinyDispatch
{
    class SerialQueue : Queue
    {
    private:
        std::thread *thread = NULL;
        std::mutex access; // access the 'queue' field
        std::mutex exec_access; // access the execution (for sync method)
        std::queue<Block> queue;
        static void serialQueueThreadLoop(SerialQueue* q);
        
        SerialQueue(std::string identifier);
        void commit(void);
        bool isEmpty();
    public:
        static Queue* get(std::string identifier);
        static Queue* global();
        
        void async(Block b);
        void sync(Block b);
                
    };
}


#endif /* SerialQueue_hpp */
