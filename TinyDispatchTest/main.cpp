//
//  main.cpp
//  TinyDispatchTest
//
//  Created by Sergey Rump (SPHERE) on 01.12.2016.
//  Copyright © 2016 sr3u. All rights reserved.
//

#include <iostream>
#include "TinyDispatch.hpp"
#include <unistd.h>

int main(int argc, const char * argv[])
{
    printf("testQueue_serial\n");
    TinyDispatch::Queue *q = TinyDispatch::Queue::get("testQueue_serial");
    q->async([](){
        printf("sleep 1\n");
        sleep(1);
        printf("wake up (1)!\n");
    });
    q->async([](){
        printf("sleep 2\n");
        sleep(1);
        printf("wake up (2)!\n");
    });
    q->sync([q](){
        q->async([](){
            printf("sleep 4\n");
            sleep(1);
            printf("wake up (4)!\n");
        });
        printf("sleep 3\n");
        sleep(1);
        printf("wake up (3)!\n");
    });
    q->sync([](){
       std::cout << "Hello, World!\n";
    });
    sleep(4);
    printf("default concurrent queue threads: %i\n",TinyDispatch::ConcurrentQueue::defaultConcurrentThreadsCount());
    printf("testQueue_concurrent (4 threads)\n");
    q = TinyDispatch::ConcurrentQueue::get("testQueue_concurrent",4);
    for(int i = 0; i < 4; i++)
    {
        q->async([i](){
            printf("sleep %i (1 sec)\n",i);
            sleep(1);
        });
    }
    q->sync([](){
        printf("sleep main (1 sec)\n");
        sleep(1);
    });
    return 0;
}
