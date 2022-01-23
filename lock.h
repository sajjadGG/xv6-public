
struct lock_t
{
    uint locked; // Is the lock held?
};

//lock.c
void initLock(struct lock_t *);
void lockAcquire(struct lock_t *);
void lockRelease(struct lock_t *);
