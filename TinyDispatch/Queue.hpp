//
//  Queue.hpp
//  TinyDispatch
//
//  Created by Sergey Rump (SPHERE) on 12.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <string>
#include <functional>
#include <thread>

namespace TinyDispatch
{
    typedef std::function<void(void)> Block;
    
    class Queue
    {
    public:
        static Queue* get(std::string identifier);
        static Queue* global();
        
        virtual void async(Block b) = 0;
        virtual void sync(Block b) = 0;
    };
}
#endif /* Queue_h */
