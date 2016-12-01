/*
 *  TinyDispatch.hpp
 *  TinyDispatch
 *
 *  Created by Sergey Rump (SPHERE) on 01.12.2016.
 *  Copyright © 2016 sr3u. All rights reserved.
 *
 */

#ifndef TinyDispatch_
#define TinyDispatch_

/* The classes below are exported */
#pragma GCC visibility push(default)
#include "Queue.hpp"
namespace TinyDispatch
{
    class TinyDispatch
    {
    public:
        void HelloWorld(const char *);
    };
}
#pragma GCC visibility pop
#endif
