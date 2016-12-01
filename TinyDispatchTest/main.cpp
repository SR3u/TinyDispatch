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
    TinyDispatch::Queue *q = TinyDispatch::Queue::get("testQueue");
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
    // insert code here...
    std::cout << "Hello, World!\n";
    sleep(10);
    return 0;
}
