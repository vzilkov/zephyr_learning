#include "threads.h"
#include <stdio.h>
#include <zephyr/kernel.h>

void hello_thread1(void *arg1, void *arg2, void *arg3){
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    while(1){
        printf("Hello, I am a thread!\n");
        k_sleep(K_MSEC(1000));
    }
}
