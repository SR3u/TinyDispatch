//
//  Queue.hpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 01.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <thread>
#include <mutex>
#include <string>
#include <queue>

namespace TinyDispatch
{
    typedef std::function<void(void)> Block;
    
    class Queue
    {
    private:
        std::thread *thread = NULL;
        std::mutex access; // access the 'queue' field
        std::mutex exec_access; // access the execution (for sync method)
        std::queue<Block> queue;
        static void queueThreadLoop(Queue* q);
        
        Queue(std::string identifier);
        void commit(void);
        bool isEmpty();
    public:
        static Queue* get(std::string identifier);
        
        void async(Block b);
        void sync(Block b);
                
    };
}


#endif /* Queue_hpp */
