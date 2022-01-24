#include "types.h"
#include "stat.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "lock.h"

void initLock(struct lock_t *lk)
{
    lk->locked = 0;
}

void lockAcquire(struct lock_t *lk)
{

    // The xchg is atomic.
    while (xchg(&lk->locked, 1) != 0)
        ;

    __sync_synchronize();
}

// Release the lock.
void lockRelease(struct lock_t *lk)
{

    __sync_synchronize();

    //atomic
    asm volatile("movl $0, %0"
                 : "+m"(lk->locked)
                 :);
}
