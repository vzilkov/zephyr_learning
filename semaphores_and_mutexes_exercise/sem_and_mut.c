#include "threads.h"
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <stddef.h>

K_MUTEX_DEFINE(mutex_print);

void print_function(char *str, int size){
    k_mutex_lock(&mutex_print, K_FOREVER);
    for (size_t i = 0; i < size; i++){
        printf("%c", *(str+i));
    }
    printf("\n");
    k_mutex_unlock(&mutex_print);
}
