#pragma once
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// #define NUM_THREADS 4
// #define QUEUE_SIZE 10

// typedef struct 
// {
//     void (*func)(void *);
//     void *arg;
// } Task;


// typedef struct 
// {
//     Task queue[QUEUE_SIZE];
//     int32_t head;
//     int32_t tail;
//     int32_t count;
//     pthread_mutex_t mutex;
//     pthread_cond_t c_not_empty;
//     pthread_cond_t c_not_full;
// } ThreadPool;

// void destroy_thread_pool(ThreadPool *pool);
// void init_thread_pool(ThreadPool* pool);
// void submit_task(ThreadPool* pool, void (*function)(void*), void* arg);
// void* thread_function(void* arg);




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
void thread_pool_destroy(ThreadPool* pool);
bool thread_pool_add_task(ThreadPool* pool, thread_func func, void *arg);
void thread_pool_wait(ThreadPool* pool);