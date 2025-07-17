#include <zephyr/kernel.h>
void hello_thread1(struct k_msgq *my_msgq, void *arg2, void *arg3);
void hello_thread2(struct k_msgq *my_msgq, void *arg2, void *arg3);