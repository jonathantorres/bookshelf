#include "csapp.h"

int readcnt;
sem_t mutex;
sem_t w;

void init()
{
    readcnt = 0;
    Sem_init(&mutex, 0, 1);
    Sem_init(&w, 0, 1);
}

void *reader(void *argp)
{
    while (1) {
        P(&mutex);
        readcnt++;
        if (readcnt == 1) {
            // first reader in
            P(&w);
        }
        V(&mutex);

        // Critical section here
        // All reading happens
        printf("reading (%d) done\n", readcnt);
        // End Critical section

        P(&mutex);
        readcnt--;
        if (readcnt == 0) {
            // last reader out
            V(&w);
        }
        V(&mutex);
    }

    return NULL;
}

void *writer(void *argp)
{
    while (1) {
        P(&w);
        P(&mutex);

        // Critical section here
        // All writing happens
        printf("writing done\n");
        // End Critical section

        if (readcnt > 0) {
            V(&mutex);
            V(&w);
        } else {
            V(&w);
            V(&mutex);
        }
    }
}

int main(void)
{
    init();

    pthread_t r1;
    pthread_t r2;
    pthread_t r3;
    pthread_t wt;

    Pthread_create(&r1, NULL, reader, NULL);
    Pthread_create(&r2, NULL, reader, NULL);
    Pthread_create(&r3, NULL, reader, NULL);
    Pthread_create(&wt, NULL, writer, NULL);

    Pthread_join(r1, NULL);
    Pthread_join(r2, NULL);
    Pthread_join(r3, NULL);
    Pthread_join(wt, NULL);

    return 0;
}
