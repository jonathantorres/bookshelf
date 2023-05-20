#include "shm.h"

/* semaphore IDs */
int *clisem, *servsem;

/* shared memory IDs */
int shmid[NBUFF];

/* ptr to message structures, which are in the shared memory segment */
Mesg *mesgptr[NBUFF];

void server();

int main(void)
{
    int i;

    /*
     * Get the shared memory segments and attach them.
     */
    for (i = 0; i < NBUFF; i++) {
        if ((shmid[i] = shmget(SHMKEY + i, sizeof(Mesg), PERMS | IPC_CREAT)) < 0) {
            printf("server: can't get shared memory %d", i);
            exit(1);
        }
        if ((mesgptr[i] = (Mesg *) shmat(shmid[i], (char *) 0, 0)) == (Mesg *) -1) {
            printf("server: can't attach shared memory %d", i);
            exit(1);
        }
    }

    /*
     * Create the two semaphores.
     */
    if ((clisem = sem_open(SEMNAME1, SEMKEY1)) < 0) {
        puts("server: can't create client semaphore");
        exit(1);
    }
    if ((servsem = sem_open(SEMNAME2, SEMKEY2)) < 0) {
        puts("server: can't create server semaphore");
        exit(1);
    }

    server();

    /*
     * Detach the shared memory segments and close the semaphores.
     * We let the client remove the shared memory segments,
     * since it'll be the last one to use them.
     */
    for (i = 0; i < NBUFF; i++) {
        if (shmdt(mesgptr[i]) < 0) {
            printf("server: can't detach shared memory %d", i);
            exit(1);
        }
    }

    sem_close(clisem);
    sem_close(servsem);

    exit(0);
}

void server()
{
    int i, n, filefd;
    char errmesg[256];

    /*
     * Wait for the client to write the filename into shared memory,
     * then try to open the file.
     */
    sem_wait(servsem);

    /* null terminate filename */
    mesgptr[0]->mesg_data[mesgptr[0]->mesg_len] = '\0';

    if ((filefd = open(mesgptr[0]->mesg_data, 0)) < 0) {
        /*
         * Error.  Format an error message and send it back
         * to the client.
         */
        sprintf(errmesg, ": can't open, %s\n", strerror(errno));
        strcat(mesgptr[0]->mesg_data, errmesg);
        mesgptr[0]->mesg_len = strlen(mesgptr[0]->mesg_data);
        /* wake up client */
        sem_post(clisem);

        /* wait for client to process */
        sem_wait(servsem);
        mesgptr[1]->mesg_len = 0;
        /* wake up client */
        sem_post(clisem);

    } else {
        /*
         * Initialize the server semaphore to the number
         * of buffers.  We know its value is 0 now, since
         * it was initialized to 0, and the client has done a
         * sem_post(), followed by our sem_wait() above.
         * What we do is increment the semaphore value
         * once for every buffer (i.e., the number of resources
         * that we have).
         */
        for (i = 0; i < NBUFF; i++) {
            sem_post(servsem);
        }

        /*
         * Read the data from the file right into shared memory.
         * The -1 in the number-of-bytes-to-read is because some
         * Unices have a bug if you try and read into the final byte
         * of a shared memory segment.
         */
        for ( ; ; ) {
            for (i = 0; i < NBUFF; i++) {
                sem_wait(servsem);
                n = read(filefd, mesgptr[i]->mesg_data, MAXMESGDATA-1);
                if (n < 0) {
                    puts("server: read error");
                    exit(1);
                }
                mesgptr[i]->mesg_len = n;
                sem_post(clisem);
                if (n == 0) {
                    goto alldone;
                }
            }
        }
alldone:
        /* we've already written the 0-length final buffer */
        close(filefd);
    }
}
