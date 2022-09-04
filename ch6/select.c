#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

#define MAXLEN 1000

int main(void)
{
    char line[MAXLEN];
    char buff[MAXLEN];
    fd_set reads;
    fd_set writes;
    int rc;

    FD_ZERO(&reads);
    FD_ZERO(&writes);
    FD_SET(0, &reads);
    FD_SET(1, &writes);

    while ((rc = select(3, &reads, &writes, NULL, NULL)) > 0) {
        if (FD_ISSET(0, &reads)) {
            ssize_t n = getline(&line, MAXLEN, 0);
            if (n > 0) {
                line[n] = '\0';
            }
        }
        if (FD_ISSET(1, &writes)) {
            ssize_t r = read(1, buff, MAXLEN);
            if (r > 0) {
                buff[r] = '\0';
                fprintf(stdout, "read message: %s", buff);
            }
        }
    }

    if (rc < 0) {
        perror("select error");
        exit(1);
    }

    return 0;
}
