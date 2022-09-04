#include <stdio.h>
#include <stdlib.h>
#include "common_threads.h"

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

counter_t *counter = NULL;

#define NUM_THREADS 50
#define NUM_COUNTS 100000

void init(counter_t *c)
{
    c->value = 0;
    Mutex_init(&c->lock);
}

void increment(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    c->value++;
    Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    c->value--;
    Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    int rc = c->value;
    Pthread_mutex_unlock(&c->lock);
    return rc;
}

void *run_counter(void *attr)
{
    if (attr) {} // remove warning
    for (int i = 0; i < NUM_COUNTS; ++i) {
        increment(counter);
    }
    return NULL;
}

int main(void)
{
    counter = malloc(sizeof(counter_t));
    init(counter);

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_t t;
        Pthread_create(&t, NULL, run_counter, NULL);
        Pthread_join(t, NULL);
    }
    printf("%d\n", get(counter));
    return 0;
}
