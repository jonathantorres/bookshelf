#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>

#define SEQFILE "seqno"
#define LOCKFILE "seqno.lock"
#define MAXBUFF 100

extern int errno;

void my_lock(int fd);
void my_unlock(int fd);

int main(void)
{
    int fd, i, n, pid, seqno;
    char buff[MAXBUFF + 1];

    pid = getpid();
    if ((fd = open(SEQFILE, 2)) < 0) {
        printf("can't open %s\n", SEQFILE);
        exit(1);
    }

    for (i = 0; i < 20; i++) {
        my_lock(fd);            /* lock the file */

        lseek(fd, 0L, 0);       /* rewind before read */
        if ((n = read(fd, buff, MAXBUFF)) <= 0) {
            printf("read error\n");
            exit(1);
        }
        buff[n] = '\0';     /* null terminate for sscanf */

        if ((n = sscanf(buff, "%d\n", &seqno)) != 1) {
            printf("sscanf error\n");
            exit(1);
        }
        printf("pid = %d, seq# = %d\n", pid, seqno);

        seqno++;        /* increment the sequence number */

        sprintf(buff, "%03d\n", seqno);
        n = strlen(buff);
        lseek(fd, 0L, 0);       /* rewind before write */

        if (write(fd, buff, n) != n) {
            printf("write error\n");
            exit(1);
        }
        my_unlock(fd);          /* unlock the file */
    }
    return 0;
}

void my_lock(int fd)
{
    lseek(fd, 0L, 0); /* rewind before lockf */

    /* 0L -> lock entire file */
    if (lockf(fd, F_LOCK, 0L) == -1) {
        perror("can't F_LOCK");
        exit(1);
    }
}

void my_unlock(int fd)
{
    lseek(fd, 0L, 0);
    if (lockf(fd, F_ULOCK, 0L) == -1) {
        perror("can't F_ULOCK");
        exit(1);
    }
}
