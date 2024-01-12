#include "csapp.h"

struct stream_data {
    char *s;
    int size;
    FILE *stream;
};

char *ptr   = NULL;
int timeout = -1;

void *thread_read(void *vargp)
{
    struct stream_data d = *(struct stream_data *)vargp;
    ptr                  = fgets(d.s, d.size, d.stream);
    timeout              = 0;
}

void *thread_sleep(void *vargp)
{
    Sleep(5);
    timeout = 1;
}

char *tfgets(char *s, int size, FILE *stream)
{
    pthread_t tid_read;
    pthread_t tid_sleep;
    struct stream_data d;

    d.s      = s;
    d.size   = size;
    d.stream = stream;

    Pthread_create(&tid_read, NULL, thread_read, (void *)&d);
    Pthread_create(&tid_sleep, NULL, thread_sleep, NULL);

    while (timeout == -1) {
        // wait 2 thread race result
    }

    if (timeout == 1) {
        Pthread_cancel(tid_read);
        return NULL;
    } else {
        Pthread_cancel(tid_sleep);
        return ptr;
    }
}

int main(int argc, char *argv[])
{
    char buf[MAXLINE];

    if (tfgets(buf, MAXLINE, stdin) == NULL) {
        printf("BOOM!\n");
    } else {
        printf("%s", buf);
    }

    return 0;
}
