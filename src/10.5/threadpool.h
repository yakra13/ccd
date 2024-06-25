#pragma once
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef void (*thread_func)(void* arg);

typedef struct ThreadTask ThreadTask;
struct ThreadTask
{
    thread_func func;
    void* arg;
    ThreadTask* next;
};

typedef struct
{
    ThreadTask* head;
    ThreadTask* tail;
    pthread_mutex_t mutex;
    pthread_cond_t task_cond;
    pthread_cond_t working_cond;
    size_t working_count;
    size_t thread_count;
    bool stop;
} ThreadPool;

ThreadPool* thread_pool_create(size_t num);
int thread_pool_destroy(ThreadPool* pool);
int thread_pool_add_task(ThreadPool* pool, thread_func func, void *arg);
int thread_pool_wait(ThreadPool* pool);