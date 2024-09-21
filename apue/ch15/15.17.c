#include "apue.h"
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define NLOOPS 1000
#define SIZE   sizeof(long) /* size of shared memory area */

static int update(long *ptr)
{
    return ((*ptr)++); /* return value before increment */
}

int main(void)
{
    int id, fd, i, counter;
    void *area;
    pid_t pid;

    id   = shmget(IPC_PRIVATE, SIZE, 0600);
    area = shmat(id, 0, 0);
    fd   = open("15.17.c", O_RDWR);

    writew_lock(fd, 0, SEEK_SET, 1);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        // parent process
        for (i = 0; i < NLOOPS; i += 2) {
            sleep(1);
            printf("parent: before lock\n");
            writew_lock(fd, 0, SEEK_SET, 1);
            printf("parent: got lock\n");

            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            un_lock(fd, 0, SEEK_SET, 1);
            printf("parent: unlock\n");
        }
    } else {
        // child process
        for (i = 1; i < NLOOPS + 1; i += 2) {
            sleep(1);
            printf("child: before lock\n");
            writew_lock(fd, 0, SEEK_SET, 1);
            printf("child: got lock\n");

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            un_lock(fd, 0, SEEK_SET, 1);
            printf("child: unlock\n");
        }
    }

    return 0;
}
