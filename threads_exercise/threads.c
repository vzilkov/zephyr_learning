#include "threads.h"
#include "sem_and_mut.h"
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <string.h>

// #include <device.h>
// #include <devicetree.h>

#include <zephyr/devicetree.h>

// #include <zephyr/drivers/fake/hww.h> // ???
#include "../modules/fakee/hww.h" // ???

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

void hello_thread1(struct k_msgq *my_msgq, void *arg2, void *arg3){
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    int msg = 0;

    k_timer_init(&timer_thread1, timer_expiry_function, timer_stop_function);
    // k_timer_start(&timer_thread1, K_MSEC(TIMER_INTERVAL_MS), K_MSEC(TIMER_INTERVAL_MS));
    
    #define MY_HWW DEVICE_DT_NAME_GET(hww_fakee) // DT_NODELABEL(hww_fakee)
    volatile struct device *dev1;
    
    // #if DT_NODE_EXISTS(DT_NODELABEL(hww_fakee))
    //     dev1 = DEVICE_DT_GET(DT_NODELABEL(hww_fakee));
    // #else
    //     #error "Node is disabled"
    // #endif
    // DT_NODE_FULL_NAME(DT_NODELABEL(hww_fakee));
    #if DT_NODE_EXISTS(DT_ALIAS(my_hw))
        dev1 = DEVICE_DT_GET(DT_ALIAS(my_hw));
    #else
        #error "woops"
    #endif
    
    if (dev1) {
        const struct fakee_driver_api *api = (const struct fakee_driver_api *)dev1->api;
        api->fakee_api_print(dev1);
    } else {
        printk("Device not found\n");
    } 

    while(1)
    {
        msg++;
        int ret = k_msgq_put(my_msgq, &msg, K_NO_WAIT);
        if (ret == 0)
        {
            printk("Produced message: %d >>>>\n", msg);
        } 
        else 
        {
            printk("Failed to produce message\n");
        }
        //specially made for the exercise without mutex or 
        // another synchronization methods
        // printf("Hello, AAAAAAAA thread1! %d\n", ++count);
        // char str[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        // print_function(str, strlen(str));
        // printk("Thread1? %d? 0x%X\n", ++(*adr), adr);        
        k_msleep(1000);
        // k_yield();
    }
}

void hello_thread2(struct k_msgq *my_msgq, void *arg2, void *arg3){
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    while(1){
        // Read from the pipe
        int msg;
        int ret = k_msgq_get(my_msgq, &msg, K_FOREVER);
        if (ret == 0) {
            printk("Received message: %d <<<<\n", msg);
        } 
        else {
            printk("Failed to receive message\n");
        }
        // printf("Bye, BBBBBBB thread2! %d\n", ++count);
        // char str[] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
        // print_function(str, strlen(str));
        // printk("Thread2! %d! 0x%X\n", ++(*adr), adr);
        // k_yield();
        // k_msleep(1000);
    }
}
