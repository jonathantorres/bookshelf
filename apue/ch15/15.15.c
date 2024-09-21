#include "apue.h"
#include <fcntl.h>
#include <sys/shm.h>

#define NLOOPS 1000
#define SIZE   sizeof(long) /* size of shared memory area */

static int update(long *ptr)
{
    return ((*ptr)++); /* return value before increment */
}

int main(void)
{
    int id, i, counter;
    void *area;
    pid_t pid;

    id   = shmget(IPC_PRIVATE, SIZE, 0600);
    area = shmat(id, 0, 0);

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) { /* parent */
        for (i = 0; i < NLOOPS; i += 2) {
            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    } else { /* child */
        for (i = 1; i < NLOOPS + 1; i += 2) {
            WAIT_PARENT();

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            TELL_PARENT(getppid());
        }
    }

    return 0;
}
