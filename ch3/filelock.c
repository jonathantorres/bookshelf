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

void my_lock(void);
void my_unlock(void);

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
        my_lock();            /* lock the file */

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
        my_unlock();          /* unlock the file */
    }
    return 0;
}

void my_lock(void)
{
    int tempfd;
    char tempfile[30];

    sprintf(tempfile, "LCK%d", getpid());

    if ((tempfd = creat(tempfile, 0444)) < 0) {
        printf("can't creat temp file\n");
        exit(1);
    }
    close(tempfd);

    while (link(tempfile, LOCKFILE) < 0) {
        if (errno != EEXIST) {
            printf("link error\n");
            exit(1);
        }
        sleep(1);
    }
    if (unlink(tempfile) < 0) {
        printf("unlink error for tempfile\n");
        exit(1);
    }
}

void my_unlock(void)
{
    if (unlink(LOCKFILE) < 0) {
        printf("unlink error for LOCKFILE\n");
        exit(1);
    }
}
