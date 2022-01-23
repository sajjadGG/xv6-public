struct lock_t
{
  uint locked; // Is the lock held?
};

void initlock(struct lock_t *lk);
void lock_acquire(struct lock_t *lk);
void lock_release(struct lock_t *lk);