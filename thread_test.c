#include "types.h"
#include "user.h"
#include "stat.h"
#include "fs.h"
#include "fcntl.h"
#include "lock.h"
#include "thread.h"

#define NUM_THREADS 5
#define TARGET_COUNT_PER_THREAD 400

uint g_counter;
struct lock_t *lt;
void *thread(void *arg)
{
    int i;
    int counter;

    sleep(10);
    printf(1, "thread %d: started...\n", *(int *)arg);

    for (i = 0; i < TARGET_COUNT_PER_THREAD; i++)
    {
        lockAcquire(lt);

        counter = g_counter;
        sleep(0);
        counter++;
        sleep(0);
        g_counter = counter;

        lockRelease(lt);
    }

    exit();
}

int main(int argc, char **argv)
{
    int i;
    int final_counter;
    int final_target = NUM_THREADS * TARGET_COUNT_PER_THREAD;

    initLock(lt);

    // Initialize counter
    g_counter = 0;

    int *args[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++)
    {

        args[i] = (int *)malloc(4);
        if (!args[i])
        {
            printf(1, "main: no mem for args  , exiting...\n");
            exit();
        }

        *args[i] = i;
    }

    printf(1, "main: running with %d threads...\n", NUM_THREADS);

    // Start all threads
    for (i = 0; i < NUM_THREADS; i++)
    {
        thread_create(thread, args[i]);
        printf(1, "main: created thread with pid \n");
    }

    // Wait for all threads

    for (i = 0; i < NUM_THREADS; i++)
    {
        printf(1, "before join %d\n", getpid());
        thread_join();
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