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

    pool = calloc(1, sizeof(*pool));
    pool->thread_count = num;

    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->task_cond), NULL);
    pthread_cond_init(&(pool->working_cond), NULL);

    pool->head = NULL;
    pool->tail = NULL;

    for (; i < num; i++)
    {
        pthread_create(&thread, NULL, thread_pool_worker, pool);
        pthread_detach(thread);
    }
    
    return pool;
}

// - [x] Locks
void thread_pool_destroy(ThreadPool* pool)
{
    ThreadTask* cur_task;
    ThreadTask* next_task;

    if (pool == NULL)
        return;

    pthread_mutex_lock(&(pool->mutex));
    
    cur_task = pool->head;
    
    while (cur_task != NULL)
    {
        next_task = cur_task->next;
        thread_task_destroy(cur_task);
        cur_task = next_task;
    }

    pool->head = NULL;
    pool->stop = true;

    pthread_cond_broadcast(&(pool->task_cond));
    pthread_mutex_unlock(&(pool->mutex));

    thread_pool_wait(pool);

    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->task_cond));
    pthread_cond_destroy(&(pool->working_cond));

    free(pool);
}

bool thread_pool_add_task(ThreadPool* pool, thread_func func, void *arg)
{
    if (pool == NULL)
        return false;

    ThreadTask* task;

    if ((task = thread_task_create(func, arg)) == NULL)
        return false;

    pthread_mutex_lock(&(pool->mutex));

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

    pthread_cond_broadcast(&(pool->task_cond));
    pthread_mutex_unlock(&(pool->mutex));

    return true;
}

void thread_pool_wait(ThreadPool* pool)
{
    if (pool == NULL)
        return;

    pthread_mutex_lock(&(pool->mutex));
    
    while (true)
    {
        if (pool->head != NULL ||
            (!pool->stop && pool->working_count != 0) ||
            (pool->stop && pool->thread_count != 0))
        {
            pthread_cond_wait(&(pool->working_cond), &(pool->mutex));
        }
        else
            break;
    }

    pthread_mutex_unlock(&(pool->mutex));    
}

static void* thread_pool_worker(void* arg)
{
    ThreadPool* pool = arg;
    ThreadTask* task;

    while(true)
    {
        pthread_mutex_lock(&(pool->mutex));

        while (pool->head == NULL && !pool->stop)
            pthread_cond_wait(&(pool->task_cond), &(pool->mutex));

        if (pool->stop)
            break;

        task = thread_task_get(pool);
        pool->working_count++;
        pthread_mutex_unlock(&(pool->mutex));

        if (task != NULL)
        {
            task->func(task->arg);
            thread_task_destroy(task);
        }

        pthread_mutex_lock(&(pool->mutex));
        pool->working_count--;

        if (!pool->stop && pool->working_count == 0 && pool->head == NULL)
            pthread_cond_signal(&(pool->working_cond));

        pthread_mutex_unlock(&(pool->mutex));
    }

    pool->thread_count--;
    pthread_cond_signal(&(pool->working_cond));
    pthread_mutex_unlock(&(pool->mutex));

    return NULL;
}

static ThreadTask* thread_task_create(thread_func func, void *arg)
{
    ThreadTask* task;

    if (func == NULL)
        return NULL;

    task = (ThreadTask*)malloc(sizeof(*task));
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