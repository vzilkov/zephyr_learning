#include "threads.h"
#include "sem_and_mut.h"
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <string.h>

static struct k_timer timer_thread1;
#define TIMER_INTERVAL_MS 100
void timer_expiry_function(struct k_timer *timer_id)
{
    char str[] = "Timer expired (str var)!";
    print_function(str, strlen(str));
    printk("Timer expired!\n");
}

// Timer stop function (optional)
void timer_stop_function(struct k_timer *timer_id)
{
    char str[] = "Timer stopped (str var)!";
    print_function(str, strlen(str));
    printk("Timer stopped!\n");
}

void hello_thread1(void *arg1, void *arg2, void *arg3){
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    unsigned int count = 0;
    unsigned int *adr = &count;

    k_timer_init(&timer_thread1, timer_expiry_function, timer_stop_function);
    k_timer_start(&timer_thread1, K_MSEC(TIMER_INTERVAL_MS), K_MSEC(TIMER_INTERVAL_MS));

    while(1){
        //specially made for the exercise without mutex or 
        // another synchronization methods
        // printf("Hello, AAAAAAAA thread1! %d\n", ++count);   
        char str[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        print_function(str, strlen(str));
        printk("Thread1? %d? 0x%X\n", ++(*adr), adr);        
        k_msleep(1000);
        k_yield();
    }
}

void hello_thread2(void *arg1, void *arg2, void *arg3){
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);
    unsigned int count = 0;
    unsigned int *adr = &count;
    while(1){
        // printf("Bye, BBBBBBB thread2! %d\n", ++count);
        char str[] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
        print_function(str, strlen(str));
        printk("Thread2! %d! 0x%X\n", ++(*adr), adr);
        k_yield();
        k_msleep(5000);
    }
}
