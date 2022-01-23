#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define NUM_THREADS 4
#define TARGET_COUNT_PER_THREAD 500
#define SEMAPHORE_NUM 0

uint g_counter;
struct lock_t lt;
void *thread(void *arg)
{
    int i;
    int counter;

    sleep(10);
    printf(1, "thread %d: started...\n", *(int *)arg);

    for (i = 0; i < TARGET_COUNT_PER_THREAD; i++)
    {
        lock_acquire(&lt);

        counter = g_counter;
        sleep(0);
        counter++;
        sleep(0);
        g_counter = counter;

        lock_release(&lt);
    }

    exit();
}

int main(int argc, char **argv)
{
    int i;
    int final_counter;
    int final_target = NUM_THREADS * TARGET_COUNT_PER_THREAD;

    initlock(&lt);

    // Initialize counter
    g_counter = 0;

    // Set up thread stuff

    // Stacks
    void *stacks[NUM_THREADS];
    // Args
    int *args[NUM_THREADS];

    // Allocate stacks and args and make sure we have them all
    // Bail if something fails
    for (i = 0; i < NUM_THREADS; i++)
    {
        stacks[i] = (void *)malloc(4096);
        if (!stacks[i])
        {
            printf(1, "main: could not get stack for thread, exiting...\n");
            exit();
        }

        args[i] = (int *)malloc(4);
        if (!args[i])
        {
            printf(1, "main: could not get memory (for arg) for thread , exiting...\n");
            exit();
        }

        *args[i] = i;
    }

    printf(1, "main: running with %d threads...\n", NUM_THREADS);

    // Start all children
    for (i = 0; i < NUM_THREADS; i++)
    {
        thread_create(thread, args[i]);
        printf(1, "main: created thread with pid \n");
    }

    // Wait for all children

    for (i = 0; i < NUM_THREADS; i++)
    {
        join();
    }

    // Check the result
    final_counter = g_counter;
    printf(1, "Final counter is %d, target is %d\n", final_counter, final_target);
    if (final_counter == final_target)
        printf(1, "TEST PASSED!\n");
    else
        printf(1, "TEST FAILED!\n");

    // Exit
    exit();
}