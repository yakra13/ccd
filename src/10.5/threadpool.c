/*10.5 Demonstrate the ability to use the following constructs associated with concurrency
Objectives
- [x] Threads
- [x] Locks
- [x] Condition variables
- [x] Atomics
- [x] Thread Pool (with graceful shutdown without memory leaks)
*/
#include <stdio.h>
#include "threadpool.h"

static void* thread_pool_worker(void* arg);
static ThreadTask* thread_task_create(thread_func func, void *arg);
static void thread_task_destroy(ThreadTask* task);
static ThreadTask* thread_task_get(ThreadPool* pool);

// - [x] Threads
// - [x] Condition variables
// - [x] Thread Pool
ThreadPool* thread_pool_create(size_t num)
{
    ThreadPool* pool;
    pthread_t thread;
    size_t i = 0;
    int err = 0;

    if (num == 0)
        num = 2;

    // Allocate memory for the thread pool
    pool = (ThreadPool*)calloc(1, sizeof(*pool));
    if (pool == NULL)
        return NULL;


    // Initialize the mutex lock and conditionals
    if ((err = pthread_mutex_init(&(pool->mutex), NULL)) != 0)
    {
        printf("pthread error mutex init: %d\n", err);
        free(pool);
        return NULL;
    }

    if ((err = pthread_cond_init(&(pool->task_cond), NULL)) != 0)
    {
        printf("pthread error cond init(task_cond): %d\n", err);
        free(pool);
        return NULL;
    }

    if ((err = pthread_cond_init(&(pool->working_cond), NULL)) != 0)
    {
        printf("pthread error cond init(working_cond): %d\n", err);
        free(pool);
        return NULL;
    }

    pool->head = NULL;
    pool->tail = NULL;

    pool->thread_count = 0;

    // Create the threads to act as workers for the thread pool
    for (; i < num; i++)
    {
        // Create each thread and on failure try the next thread.
        // This results in fewer workers than specified.
        if ((err = pthread_create(&thread, NULL, thread_pool_worker, pool)) != 0)
        {
            printf("pthread error create: %d\n", err);
            continue;
        }

        // On error either the specified thread is not joinable or this thread wasn't found
        // Either option should never happen so if we error here something is horribly wrong.
        if ((err = pthread_detach(thread)) != 0)
        {
            printf("pthread error detach: %d\n", err);
            free(pool);
            return NULL;
        }

            pool->thread_count++;
    }
    
    return pool;
}

// - [x] Locks
int thread_pool_destroy(ThreadPool* pool)
{
    int err = 0;
    ThreadTask* cur_task;
    ThreadTask* next_task;

    if (pool == NULL)
    {
        printf("Error thread pool is null.\n");
        return -1;
    }

    if ((err = pthread_mutex_lock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex lock: %d\n", err);
        free(pool);
        return err;
    }
    
    // Ultimately we want to complete all the tasks here if they are not already
    cur_task = pool->head;
    
    while (cur_task != NULL)
    {
        next_task = cur_task->next;
        thread_task_destroy(cur_task);
        cur_task = next_task;
    }

    pool->head = NULL;
    pool->stop = true;

    // At this point most of the errors really don't matter much.
    // We are closing out the thread pool and preparing to free it.
    // If we got this far the results have been printed and we are closing
    // the program so we at least ensure we free the memory and let
    // the user know if something errors.

    if ((err = pthread_cond_broadcast(&(pool->task_cond))) != 0)
    {
        printf("pthread error cond broadcast: %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
        free(pool);
        return err;
    }

    if ((err = thread_pool_wait(pool)) != 0)
    {
        printf("Error waiting for tasks: %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_mutex_destroy(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex destroy: %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_cond_destroy(&(pool->task_cond))) != 0)
    {
        printf("pthread error cond destroy(task_cond): %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_cond_destroy(&(pool->working_cond))) != 0)
    {
        printf("pthread error cond destroy(working_cond): %d\n", err);
        free(pool);
        return err;
    }

    free(pool);

    return err;
}

// Add a task to the thread pool
int thread_pool_add_task(ThreadPool* pool, thread_func func, void *arg)
{
    int err = 0;
    ThreadTask* task;

    if (pool == NULL)
    {
        printf("Error thread pool is null.\n");
        return -1;
    }

    if ((task = thread_task_create(func, arg)) == NULL)
        return err;

    if ((err = pthread_mutex_lock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex lock: %d\n", err);
        return err;
    }

    // Append tasks to the circular list
    if (pool->head == NULL)
    {
        pool->head = task;
        pool->tail = pool->head;
    }
    else
    {
        pool->tail->next = task;
        pool->tail = task;
    }

    // Unblocks threads with this condition
    // With the way the pool is designed this should never error
    if ((err = pthread_cond_broadcast(&(pool->task_cond))) != 0)
    {
        printf("pthread error cond broadcast: %d\n", err);
    }

    // As far as I am aware an error with unlock means the current thread
    // does not own the mutex so continuing on should be fine.
    if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
        err = 0;
    }

    return err;
}

int thread_pool_wait(ThreadPool* pool)
{
    int err = 0;
    if (pool == NULL)
    {
        printf("Error thread pool is null.\n");
        return -1;
    }

    if ((err = pthread_mutex_lock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex lock: %d\n", err);
        return err;
    }
    
    while (true)
    {
        if (pool->head != NULL ||
            (!pool->stop && pool->working_count != 0) ||
            (pool->stop && pool->thread_count != 0))
        {
            // This should only error if the lock is not currently owned by this thread
            if ((err = pthread_cond_wait(&(pool->working_cond), &(pool->mutex))) != 0)
            {
                printf("pthread error cond wait: %d\n", err);
                return err;
            }
        }
        else
            break;
    }

    // As far as I am aware an error with unlock means the current thread
    // does not own the mutex so continuing on should be fine.
    if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
        err = 0;
    }

    return err;
}

// Worker function to be run by each thread to process a task.
static void* thread_pool_worker(void* arg)
{
    ThreadPool* pool = arg;
    ThreadTask* task;
    int err = 0;

    if (pool == NULL)
    {
        printf("Worker was given a null pool.\n");
        return NULL;
    }

    while(true)
    {
        if ((err = pthread_mutex_lock(&(pool->mutex))) != 0)
        {
            printf("worker error pthread mutex lock: %d\n", err);
            return NULL;
        }

        while (pool->head == NULL && !pool->stop)
            if ((err = pthread_cond_wait(&(pool->task_cond), &(pool->mutex))) != 0)
            {
                printf("worker error pthread cond wait: %dn", err);
            }

        if (pool->stop)
            break;

        task = thread_task_get(pool);
        pool->working_count++;

        // As far as I am aware an error with unlock means the current thread
        // does not own the mutex so continuing on should be fine.
        if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
        {
            printf("worker pthread error mutex unlock: %d\n", err);
        }

        if (task != NULL)
        {
            task->func(task->arg);
            thread_task_destroy(task);
        }

        if ((err = pthread_mutex_lock(&(pool->mutex))) != 0)
        {
            printf("worker error pthread mutex lock: %d\n", err);
            return NULL;
        }

        pool->working_count--;

        if (!pool->stop && pool->working_count == 0 && pool->head == NULL)
            if ((err = pthread_cond_signal(&(pool->working_cond))) != 0)
            {
                printf("worker error pthread cond signal: %d\n", err);
            }
        // As far as I am aware an error with unlock means the current thread
        // does not own the mutex so continuing on should be fine.
        if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
        {
            printf("pthread error mutex unlock: %d\n", err);
        }
    }

    pool->thread_count--;
    if ((err = pthread_cond_signal(&(pool->working_cond))) != 0)
    {
        printf("worker error pthread cond signal: %d\n", err);
    }

    // As far as I am aware an error with unlock means the current thread
    // does not own the mutex so continuing on should be fine.
    if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
    }

    return NULL;
}

// Allocates memory for a task and sets its attributes
static ThreadTask* thread_task_create(thread_func func, void *arg)
{
    ThreadTask* task;

    if (func == NULL)
    {
        printf("Error func null in create task.\n");
        return NULL;
    }

    task = (ThreadTask*)malloc(sizeof(*task));
    if (task == NULL)
    {
        printf("Error malloc create task.\n");
        return NULL;
    }

    task->func = func;
    task->arg = arg;
    task->next = NULL;

    return task;
}

// Just frees the tasks allocated memory
static void thread_task_destroy(ThreadTask* task)
{
    if (task == NULL)
        return;

    free(task);
}

// Removes a task from the list and returns it.
static ThreadTask* thread_task_get(ThreadPool* pool)
{
    ThreadTask* task;

    if (pool == NULL)
        return NULL;

    if ((task = pool->head) == NULL)
        return NULL;

    if (task->next == NULL)
        pool->tail = NULL;

    pool->head = task->next;

    return task;
}