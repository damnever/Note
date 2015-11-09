#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

/*
 * Using condition variable as synchronization primitive is good enough.
 * I don't know where and how and when can reuse it.
 */

typedef struct _mypthr_barrier_t {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    int count;
} mypthr_barrier_t;

int mypthr_barrier_init(mypthr_barrier_t *barrier, int count);
int mypthr_barrier_destroy(mypthr_barrier_t *barrier);
int mypthr_barrier_wait(mypthr_barrier_t *barrier);
void *thr_fn1(void *arg);
void *thr_fn2(void *arg);

mypthr_barrier_t barrier1, barrier2;

int
main()
{
    int err;
    pthread_t tid1, tid2;

    mypthr_barrier_init(&barrier1, 3);
    mypthr_barrier_init(&barrier2, 3);

    if ((err = pthread_create(&tid1, NULL, thr_fn1, NULL)) != 0) {
        fprintf(stderr, "pthread create error: %s\n", strerror(errno));
    }
    if ((err = pthread_create(&tid2, NULL, thr_fn2, NULL)) != 0) {
        fprintf(stderr, "pthread create error: %s\n", strerror(errno));
    }

    mypthr_barrier_wait(&barrier1);
    printf("Main Thread: task1 done\n");

    mypthr_barrier_wait(&barrier2);
    printf("Main Thread: task2 done\n");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("Main thread stoping\n");


    return 0;
}

int
mypthr_barrier_init(mypthr_barrier_t *barrier, int count)
{
    int ret;

    barrier->count = count;
    if ((barrier = (mypthr_barrier_t*)malloc(sizeof(mypthr_barrier_t))) == NULL) {
        return -1;
    }
    if ((ret = pthread_cond_init(&barrier->cond, NULL)) != 0) {
        return ret;
    }
    if ((ret = pthread_mutex_init(&barrier->mutex, NULL)) != 0) {
        return ret;
    }

    return 0;
}

int
mypthr_barrier_destroy(mypthr_barrier_t *barrier)
{
    int ret;

    barrier->count = 0;
    if ((ret = pthread_cond_destroy(&barrier->cond)) != 0) {
        return ret;
    }
    if ((ret = pthread_mutex_destroy(&barrier->mutex)) != 0) {
        return ret;
    }
    free(barrier);

    return 0;
}

int
mypthr_barrier_wait(mypthr_barrier_t *barrier)
{
    int ret;

    if ((ret = pthread_mutex_lock(&barrier->mutex)) != 0) {
        return ret;
    }
    barrier->count -= 1;
    if ((ret = pthread_mutex_unlock(&barrier->mutex)) != 0) {
        return ret;
    }
    if ((ret = pthread_cond_broadcast(&barrier->cond)) != 0) {
        return ret;
    }

    if ((ret = pthread_mutex_lock(&barrier->mutex)) != 0) {
        return ret;
    }
    while (0 != barrier->count) {
        if ((ret = pthread_cond_wait(&barrier->cond, &barrier->mutex)) != 0) {
            return ret;
        }
    }
    if ((ret = pthread_mutex_unlock(&barrier->mutex)) != 0) {
        return ret;
    }

    return 0;
}

void *thr_fn1(void *arg)
{
    pthread_t tid = pthread_self();

    printf("Thread %lu started\n", tid);
    sleep(1);
    printf("Thread %lu running task1\n", tid);
    sleep(2);
    mypthr_barrier_wait(&barrier1);

    printf("Thread %lu running task2\n", tid);
    sleep(1);
    mypthr_barrier_wait(&barrier2);

    return ((void *)0);
}

void *thr_fn2(void *arg)
{
    pthread_t tid = pthread_self();

    printf("Thread %lu started\n", tid);
    sleep(1);
    printf("Thread %lu running task1\n", tid);
    sleep(1);
    mypthr_barrier_wait(&barrier1);

    printf("Thread %lu running task2\n", tid);
    sleep(2);
    mypthr_barrier_wait(&barrier2);

    return ((void *)0);
}
