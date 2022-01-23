#include "types.h"
#include "stat.h"
#include "user.h"
#include "lock.h"

/* Possible states of a thread: */
#define FREE 0x0
#define RUNNING 0x1
#define RUNNABLE 0x2

#define STACK_SIZE 8192
#define MAX_THREAD 4
