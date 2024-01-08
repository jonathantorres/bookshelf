#include "csapp.h"

void *thread(void *vargp);

int main(int argc, char *argv[])
{
    int n;

    if (argc != 2) {
        puts("must provide a value for n");
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);
    pthread_t tid;

    for (int i = 0; i < n; i++) {
        Pthread_create(&tid, NULL, thread, NULL);
        Pthread_join(tid, NULL);
    }
    exit(EXIT_SUCCESS);
}

void *thread(void *vargp)
{
    printf("Hello, world!\n");
    return NULL;
}
