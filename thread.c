#include "types.h"
#include "stat.h"
#include "user.h"

/* Possible states of a thread: */
#define FREE 0x0
#define RUNNING 0x1
#define RUNNABLE 0x2

#define STACK_SIZE 8192
#define MAX_THREAD 4

struct thread
{
    char stack[STACK_SIZE]; /* the thread's stack */
    int state;              /* FREE, RUNNING, RUNNABLE */

    struct
    {
        uint sp, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
        uint ra;
    } reg_state;
};
struct thread all_thread[MAX_THREAD];
struct thread *current_thread;

void thread_init(void)
{

    current_thread = &all_thread[0]; //main
    current_thread->state = RUNNING;
}
//TODO: args
void thread_create(void (*func)())
{
    struct thread *t;

    for (t = all_thread; t < all_thread + MAX_THREAD; t++)
    {
        if (t->state == FREE)
            break;
    }
    t->state = RUNNABLE;
    // YOUR CODE HERE
    t->reg_state.ra = (uint)func;
    t->reg_state.sp = (uint)(t->stack + STACK_SIZE);
}