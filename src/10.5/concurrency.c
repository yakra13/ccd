/*10.5 Demonstrate the ability to use the following constructs associated with concurrency
Objectives
- [x] Threads
- [x] Locks
- [x] Condition variables
- [x] Atomics
- [x] Thread Pool (with graceful shutdown without memory leaks)
*/

#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "threadpool.h"

static const size_t num_threads = 4;
static const size_t num_items   = 40;

_Atomic int32_t counter = 0;
// - [x] Atomics
void process_task(void* arg)
{
    int32_t task_number = *((int32_t*)arg);
    printf("%d ", task_number);
    fflush(stdout);
    sleep(1);

    atomic_fetch_add(&counter, 1);
}

int32_t main(int32_t argc, char** argv)
{
    ThreadPool* pool;
    int32_t* vals;

    pool = thread_pool_create(num_threads);
    vals = calloc(num_items, sizeof(*vals));
    
    printf("Processing tasks:\n");
    for (size_t i = 0; i < num_items; i++)
    {
        vals[i] = i;
        thread_pool_add_task(pool, process_task, vals + i);
    }

    thread_pool_wait(pool); 

    printf("\nResults:\n");

    for (size_t i = 0; i < num_items; i++)
    {
        printf("%d ", vals[i]);
        fflush(stdout);
    }
    printf("\n");

    printf("Atomic counter = %d\n", counter);

    free(vals);

    thread_pool_destroy(pool);

    return EXIT_SUCCESS;
}

