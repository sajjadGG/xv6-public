#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "lock.h"
#include "user.h"

void initlock(struct lock_t *lk)
{
    lk->locked = 0;
}

// Acquire the lock.
// Loops (spins) until the lock is acquired.
// Holding a lock for a long time may cause
// other CPUs to waste time spinning to acquire it.
void lock_acquire(struct lock_t *lk)
{
    pushcli(); // disable interrupts to avoid deadlock.

    // The xchg is atomic.
    while (xchg(&lk->locked, 1) != 0)
        ;

    __sync_synchronize();
}

// Release the lock.
void lock_release(struct lock_t *lk)
{

    __sync_synchronize();

    //atomic
    asm volatile("movl $0, %0"
                 : "+m"(lk->locked)
                 :);

    popcli();
}
