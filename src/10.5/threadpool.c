/*10.5 Demonstrate the ability to use the following constructs associated with concurrency
Objectives
- [x] Threads
- [x] Locks
- [x] Condition variables
- [x] Atomics
- [x] Thread Pool (with graceful shutdown without memory leaks)
*/
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

    if (num == 0)
        num = 2;

    pool = (ThreadPool*)calloc(1, sizeof(*pool));
    if (pool == NULL)
        return NULL;

    pool->thread_count = num;

    if ((err = pthread_mutex_init(&(pool->mutex), NULL) != 0)
    {
        printf("pthread error mutex init: %d\n", err);
        free(pool);
        return NULL;
    }

    if ((err = pthread_cond_init(&(pool->task_cond), NULL) != 0)
    {
        printf("pthread error cond init(task_cond): %d\n", err);
        free(pool);
        return NULL;
    }

    if ((err = pthread_cond_init(&(pool->working_cond), NULL) != 0)
    {
        printf("pthread error cond init(working_cond): %d\n", err);
        free(pool);
        return NULL;
    }

    pool->head = NULL;
    pool->tail = NULL;

    for (; i < num; i++)
    {
        if ((err = pthread_create(&thread, NULL, thread_pool_worker, pool) != 0)
        {
            printf("pthread error create: %d\n", err);
            free(pool);
            return NULL;
        }

        if ((err = pthread_detach(thread) != 0)
        {
            printf("pthread error detach: %d\n", err);
            free(pool);
            return NULL;
        }
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
        printf("Error thread pool is null.\n")
        return -1;
    }

    if ((err = pthread_mutex_lock(&(pool->mutex)) != 0)
    {
        printf("pthread error mutex lock: %d\n", err);
        free(pool);
        return err;
    }
    
    cur_task = pool->head;
    
    while (cur_task != NULL)
    {
        next_task = cur_task->next;
        thread_task_destroy(cur_task);
        cur_task = next_task;
    }

    pool->head = NULL;
    pool->stop = true;

    if ((err = pthread_cond_broadcast(&(pool->task_cond)) != 0)
    {
        printf("pthread error cond broadcast: %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_mutex_unlock(&(pool->mutex)) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
    }

    if ((err = thread_pool_wait(pool) != 0)
    {
        printf("Error waiting for tasks: %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_mutex_destroy(&(pool->mutex)) != 0)
    {
        printf("pthread error mutex destroy: %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_cond_destroy(&(pool->task_cond)) != 0)
    {
        printf("pthread error cond destroy(task_cond): %d\n", err);
        free(pool);
        return err;
    }

    if ((err = pthread_cond_destroy(&(pool->working_cond)) != 0)
    {
        printf("pthread error cond destroy(working_cond): %d\n", err);
        free(pool);
        return err;
    }

    free(pool);

    return err;
}

int thread_pool_add_task(ThreadPool* pool, thread_func func, void *arg)
{
    int err = 0;
    ThreadTask* task;

    if (pool == NULL)
    {
        printf("Error thread pool is null.\n")
        return -1;
    }

    if ((task = thread_task_create(func, arg)) == NULL)
        return err;

    if ((err = pthread_mutex_lock(&(pool->mutex)) != 0)
    {
        printf("pthread error mutex lock: %d\n", err);
        return err;
    }

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

    if ((err = pthread_cond_broadcast(&(pool->task_cond)) != 0)
    {
        printf("pthread error cond broadcast: %d\n", err);
        return err;
    }

    if ((err = pthread_mutex_unlock(&(pool->mutex)) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
    }

    return err;
}

int thread_pool_wait(ThreadPool* pool)
{
    int err = 0;
    if (pool == NULL)
    {
        printf("Error thread pool is null.\n")
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
            if ((err = pthread_cond_wait(&(pool->working_cond), &(pool->mutex))) != 0)
            {
                printf("pthread error cond wait: %d\n", err);
                return err;
            }
        }
        else
            break;
    }

    if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
    }

    return err;
}

static void* thread_pool_worker(void* arg)
{
    ThreadPool* pool = arg;
    ThreadTask* task;
    int err = 0;

    if (pool == NULL)
    {
        printf("Worker was given a null pool.\n");
        return;
    }

    while(true)
    {
        if ((err = pthread_mutex_lock(&(pool->mutex))) != 0)
        {
            printf("worker error pthread mutex lock: %d\n", err);
            return NULL;
        }

        while (pool->head == NULL && !pool->stop)
            if ((err = pthread_cond_wait(&(pool->task_cond), &(pool->mutex)) != 0)
            {
                printf("worker error pthread cond wait: %dn", err)
            }

        if (pool->stop)
            break;

        task = thread_task_get(pool);
        pool->working_count++;

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
            if ((err = pthread_cond_signal(&(pool->working_cond)) != 0)
            {
                printf("worker error pthread cond signal: %d\n", err);
            }

        if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
        {
            printf("pthread error mutex unlock: %d\n", err);
        }
    }

    pool->thread_count--;
    if ((err = pthread_cond_signal(&(pool->working_cond)) != 0)
    {
        printf("worker error pthread cond signal: %d\n", err);
    }

    if ((err = pthread_mutex_unlock(&(pool->mutex))) != 0)
    {
        printf("pthread error mutex unlock: %d\n", err);
    }

    return NULL;
}

static ThreadTask* thread_task_create(thread_func func, void *arg)
{
    ThreadTask* task;

    if (func == NULL)
    {
        printf('Error func null in create task.\n');
        return NULL;
    }

    task = (ThreadTask*)malloc(sizeof(*task));
    if (task == NULL)
    {
        printf('Error malloc create task.\n');
        return NULL;
    }

    task->func = func;
    task->arg = arg;
    task->next = NULL;

    return task;
}

static void thread_task_destroy(ThreadTask* task)
{
    if (task == NULL)
        return;

    free(task);
}

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