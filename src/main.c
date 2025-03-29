/* main.c - Synchronization demo */

/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "threads.h"

#define HELLO_THREAD1_STACK_SIZE 128
#define HELLO_THREAD1_PRIO 7
K_THREAD_STACK_DEFINE(hello_thread1_stack, HELLO_THREAD1_STACK_SIZE);
struct k_thread hello_thread1_data;

int main(void)
{
	k_thread_create(&hello_thread1_data, hello_thread1_stack, HELLO_THREAD1_STACK_SIZE,
					hello_thread1, NULL, NULL, NULL, HELLO_THREAD1_PRIO, 0, K_NO_WAIT);
	uint32_t count = 0;
	while(1){
		printk("Main thread! %d\n", count++);
		k_sleep(K_MSEC(1000));
	}
	return 0;
}
