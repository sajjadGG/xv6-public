#include "types.h"
#include "stat.h"
#include "user.h"

/* Possible states of a thread: */
#define FREE 0x0
#define RUNNING 0x1
#define RUNNABLE 0x2

#define STACK_SIZE 8192
#define MAX_THREAD 4

void thread_create(void (*start_routine)(void *), void *arg)
{
    void *np = malloc(STACK_SIZE);
    int return_c;
    return_c = clone(np, STACK_SIZE);
    if (return_c == 0)
    {
        (*start_routine)(arg);
        exit();
    }
}

void thread_join(void)
{
    join();
}