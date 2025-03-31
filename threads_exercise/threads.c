#include "threads.h"
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

void hello_thread1(void *arg1, void *arg2, void *arg3){
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    unsigned int count = 0;
    while(1){
        printf("Hello, I am a thread1! %d\n", count++);
        k_msleep(500);
    }
}

void hello_thread2(void *arg1, void *arg2, void *arg3){
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    unsigned int count = 0;
    while(1){
        printf("Bye, I am a thread2! %d\n", count++);
        k_msleep(100);
    }
}
