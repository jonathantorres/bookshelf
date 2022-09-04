#include "shm.h"

/* semaphore IDs */
int *clisem, *servsem;

/* shared memory IDs */
int shmid[NBUFF];

/* ptr to message structures, which are in the shared memory segment */
Mesg *mesgptr[NBUFF];

void client();

int main(void)
{
    int i;

    /*
     * Get the shared memory segments and attach them.
     * We don't specify IPC_CREAT, assuming the server creates them.
     */
    for (i = 0; i < NBUFF; i++) {
        if ((shmid[i] = shmget(SHMKEY + i, sizeof(Mesg), 0)) < 0) {
            printf("client: can't get shared memory %d\n", i);
            exit(1);
        }
        if ((mesgptr[i] = (Mesg *) shmat(shmid[i], (char *) 0, 0)) == (Mesg *) -1) {
            printf("client: can't attach shared memory %d\n", i);
        }
    }

    /*
     * Open the two semaphores.
     */
    if ((clisem = sem_open(SEMNAME1, SEMKEY1)) < 0) {
        printf("client: can't open client semaphore\n");
        exit(1);
    }
    if ((servsem = sem_open(SEMNAME2, SEMKEY2)) < 0) {
        printf("client: can't open server semaphore\n");
        exit(1);
    }

    client();

    /*
     * Detach and remove the shared memory segments and
     * close the semaphores.
     */
    for (i = 0; i < NBUFF; i++) {
        if (shmdt(mesgptr[i]) < 0) {
            printf("client: can't detach shared memory %d\n", i);
            exit(1);
        }
        if (shmctl(shmid[i], IPC_RMID, (struct shmid_ds *) 0) < 0) {
            printf("client: can't remove shared memory %d\n", i);
            exit(1);
        }
    }

    sem_close(clisem);
    sem_close(servsem);

    exit(0);
}

void client()
{
    int i, n;

    /*
     * Read the filename from standard input, write it to shared memory.
     */

    /* wait for server to initialize */
    sem_wait(clisem);
    if (fgets(mesgptr[0]->mesg_data, MAXMESGDATA, stdin) == NULL) {
        printf("filename read error\n");
        exit(1);
    }

    n = strlen(mesgptr[0]->mesg_data);
    if (mesgptr[0]->mesg_data[n-1] == '\n') {
        n--; /* ignore newline from fgets() */
    }
    mesgptr[0]->mesg_len = n;
    sem_post(servsem); /* wake up server */

    for ( ; ; ) {
        for (i = 0; i < NBUFF; i++) {
            sem_wait(clisem);
            if ((n = mesgptr[i]->mesg_len) <= 0) {
                goto alldone;
            }
            if (write(1, mesgptr[i]->mesg_data, n) != n) {
                printf("data write error\n");
                exit(1);
            }
            sem_post(servsem);
        }
    }

alldone:
    if (n < 0) {
        printf("data read error\n");
        exit(1);
    }
}
