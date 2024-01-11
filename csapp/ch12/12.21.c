#include "csapp.h"

int writecnt;
sem_t mutex;
sem_t r;

void init()
{
    writecnt = 0;
    Sem_init(&mutex, 0, 1);
    Sem_init(&r, 0, 1);
}

void *reader(void *argp)
{
    while (1) {
        P(&r);

        // Critical section here
        // All reading happens
        printf("reading (%d) done\n", writecnt);
        // End Critical section

        V(&r);
    }

    return NULL;
}

void *writer(void *argp)
{
    while (1) {
        P(&mutex);
        writecnt++;
        if (writecnt == 1) {
            // first writer in
            P(&r);
        }
        V(&mutex);

        // Critical section here
        // All writing happens
        printf("writing (%d) done\n", writecnt);
        // End Critical section

        P(&mutex);
        writecnt--;
        if (writecnt == 0) {
            // last writer out
            V(&r);
        }
        V(&mutex);
    }
}

int main(void)
{
    init();

    pthread_t r1;
    pthread_t r2;
    pthread_t w1;
    pthread_t w2;

    Pthread_create(&r1, NULL, reader, NULL);
    Pthread_create(&r2, NULL, reader, NULL);
    Pthread_create(&w1, NULL, writer, NULL);
    Pthread_create(&w2, NULL, writer, NULL);

    Pthread_join(r1, NULL);
    Pthread_join(r2, NULL);
    Pthread_join(w1, NULL);
    Pthread_join(w2, NULL);

    return 0;
}
