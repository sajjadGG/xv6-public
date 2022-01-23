
struct lock_t
{
    uint locked; // Is the lock held?
};

//lock.c
void initlock(struct lock_t *);
void lock_acquire(struct lock_t *);
void lock_release(struct lock_t *);
