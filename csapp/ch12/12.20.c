#include "csapp.h"

int n;
sem_t mutex;
sem_t w;

void init()
{
    n = 0;
    Sem_init(&mutex, 0, 1);
    Sem_init(&w, 0, 1);
}

void *reader(void *argp)
{
    while (1) {
        P(&mutex);
        P(&w);

        if (n == 0) {
            // access is for writers
            V(&w);
            V(&mutex);
            continue;
        }

        // Critical section here
        // All reading happens
        printf("reading - %u (%d) done\n", Pthread_self(), n);
        // End Critical section

        // give access to a writer
        n = 0;
        V(&mutex);
        V(&w);
    }

    return NULL;
}

void *writer(void *argp)
{
    while (1) {
        P(&mutex);
        P(&w);

        if (n == 1) {
            // access is for readers
            V(&w);
            V(&mutex);
            continue;
        }

        // Critical section here
        // All writing happens
        printf("writing - %u (%d) done\n", Pthread_self(), n);
        // End Critical section

        // give access to a reader
        n = 1;
        V(&mutex);
        V(&w);
    }
}

int main(void)
{
    init();

    /* 5 readers and a single writer*/
    pthread_t r1;
    pthread_t r2;
    pthread_t r3;
    pthread_t r4;
    pthread_t r5;
    pthread_t wt;

    Pthread_create(&r1, NULL, reader, NULL);
    Pthread_create(&r2, NULL, reader, NULL);
    Pthread_create(&r3, NULL, reader, NULL);
    Pthread_create(&r4, NULL, reader, NULL);
    Pthread_create(&r5, NULL, reader, NULL);
    Pthread_create(&wt, NULL, writer, NULL);

    Pthread_join(r1, NULL);
    Pthread_join(r2, NULL);
    Pthread_join(r3, NULL);
    Pthread_join(r4, NULL);
    Pthread_join(r5, NULL);
    Pthread_join(wt, NULL);

    return 0;
}
