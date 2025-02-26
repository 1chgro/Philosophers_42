# THREADS

## Overview
Threads in C provide a way to execute multiple tasks concurrently within a single process.

## Visualization
Process
|
|-- Thread 1 (Registers, Stack, PC)
|-- Thread 2 (Registers, Stack, PC)
|-- Thread 3 (Registers, Stack, PC)

(All share Code, Heap, and Open Files)

## Key Concepts
- **Threads vs. Processes**: Threads share memory; processes have separate memory spaces.
- **POSIX Threads (pthreads)**: Standardized API for thread management in C.
- **Synchronization Mechanisms**:
  - **Mutexes**: Prevents multiple threads from accessing a resource simultaneously.
  - **Semaphores**: Controls access to a resource with counters.
  - **Condition Variables**: Allows threads to wait for a condition to be met.
  - **Spinlocks**: Busy-wait locks for quick synchronization.

## Thread Lifecycle
1. **Created** -> Thread is initialized but not yet running.
2. **Runnable** -> Ready to run, waiting for CPU time.
3. **Running** -> Executing code.
4. **Blocked** -> Waiting for I/O or a lock.
5. **Terminated** -> Execution finished or canceled.

## POSIX Threads API
### Creating and Managing Threads

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(void *arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
    return 0;
}
```

### Mutex Example

```c
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;
int counter = 0;

void *increment(void *arg) {
    pthread_mutex_lock(&lock);
    counter++;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    printf("Counter: %d\n", counter);
    return 0;
}
```

## Performance Considerations

- **Context Switching Overhead**: Excessive threads can slow performance.
- **Race Conditions**: Use mutexes and synchronization.
- **Deadlocks**: Avoid circular dependencies.
- **False Sharing**: Optimize memory layout to minimize cache contention.

## Summary
Threads in C enable concurrent execution but require careful synchronization to ensure data consistency and avoid common pitfalls like race conditions and deadlocks.
