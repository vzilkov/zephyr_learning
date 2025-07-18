/* main.c - Synchronization demo */

/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "threads.h"

#define HELLO_THREAD1_STACK_SIZE 1024
#define HELLO_THREAD1_PRIO 5
K_THREAD_STACK_DEFINE(hello_thread1_stack, HELLO_THREAD1_STACK_SIZE);
struct k_thread hello_thread1_data;

#define HELLO_THREAD2_STACK_SIZE 1024
#define HELLO_THREAD2_PRIO 5
K_THREAD_STACK_DEFINE(hello_thread2_stack, HELLO_THREAD2_STACK_SIZE);
struct k_thread hello_thread2_data;

#define MSG_QUEUE_SIZE 10
#define MSG_SIZE sizeof(int)
K_MSGQ_DEFINE(my_msgq, MSG_SIZE, MSG_QUEUE_SIZE, 4);

int main(void)
{
	k_thread_create(&hello_thread1_data, hello_thread1_stack, HELLO_THREAD1_STACK_SIZE,
					hello_thread1, (struct k_msgq*) &my_msgq, NULL, NULL, HELLO_THREAD1_PRIO, 0, K_MSEC(1));
	k_thread_create(&hello_thread2_data, hello_thread2_stack, HELLO_THREAD2_STACK_SIZE,
					hello_thread2, (struct k_msgq*) &my_msgq, NULL, NULL, HELLO_THREAD2_PRIO, 0, K_MSEC(0));
	
	// k_thread_start(&hello_thread2_data);
	// k_thread_start(&hello_thread1_data);
	
	return 0;
}
