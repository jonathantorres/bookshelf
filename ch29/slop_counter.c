#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "common_threads.h"

#define NUMCPUS 4

typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;

counter_t *counter = NULL;

#define NUM_THREADS 50
#define NUM_COUNTS 100000

void init(counter_t *c, int threshold)
{
    c->global = 0;
    c->threshold = threshold;
    Mutex_init(&c->glock);
    for (int i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        Mutex_init(&c->llock[i]);
    }
}

void update(counter_t *c, int thread_id, int amt)
{
    int cpu = thread_id%NUMCPUS;
    Pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {
        Pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        Pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    Pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c)
{
    Pthread_mutex_lock(&c->glock);
    int val = c->global;
    Pthread_mutex_unlock(&c->glock);
    return val;
}

void *run_counter(void *attr)
{
    if (attr) {} // remove warning
    for (int i = 0; i < NUM_COUNTS; ++i) {
        update(counter, *(int *)attr, 1);
    }
    return NULL;
}

int main(void)
{
    counter = malloc(sizeof(counter_t));
    init(counter, 1);

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_t t;
        Pthread_create(&t, NULL, run_counter, &i);
        Pthread_join(t, NULL);
    }
    printf("%d\n", get(counter));
    return 0;
}
