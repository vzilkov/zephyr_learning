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
        //specially made for the exercise without mutex or 
        // another synchronization methods
        printf("Hello, AAAAAAAA thread1! %d\n", ++count);
    }
}

void hello_thread2(void *arg1, void *arg2, void *arg3){
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    unsigned int count = 0;
    while(1){
        printf("Bye, BBBBBBB thread2! %d\n", ++count);
    }
}
