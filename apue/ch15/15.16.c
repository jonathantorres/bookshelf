#include "apue.h"
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define NLOOPS 1000
#define SIZE   sizeof(long) /* size of shared memory area */

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

static int update(long *ptr)
{
    return ((*ptr)++); /* return value before increment */
}

int main(void)
{
    int shmid, semid, i, counter;
    void *area;
    pid_t pid;
    struct sembuf ops[1];
    union semun opts;

    shmid = shmget(IPC_PRIVATE, SIZE, 0600);
    area  = shmat(shmid, 0, 0);

    semid    = semget(IPC_PRIVATE, 2, IPC_CREAT | S_IWUSR | S_IRUSR);
    opts.val = 1;

    semctl(semid, 0, SETVAL, opts);
    opts.val = 0;
    semctl(semid, 1, SETVAL, opts);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) { /* parent */
        ops[0].sem_flg = 0;

        for (i = 0; i < NLOOPS; i += 2) {
            ops[0].sem_num = 0;
            ops[0].sem_op  = -1;
            semop(semid, ops, 1);

            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            ops[0].sem_num = 1;
            ops[0].sem_op  = 1;
            semop(semid, ops, 1);
        }
    } else { /* child */
        ops[0].sem_num = 0;
        ops[0].sem_flg = 0;
        for (i = 1; i < NLOOPS + 1; i += 2) {
            ops[0].sem_num = 1;
            ops[0].sem_op  = -1;
            semop(semid, ops, 1);

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            ops[0].sem_num = 0;
            ops[0].sem_op  = 1;
            semop(semid, ops, 1);
        }

        semctl(semid, 0, IPC_RMID);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
