#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define COUNT    20000
#define BUFFSIZE 128

char buff[BUFFSIZE];

int main(void)
{
    int i;
    int pipefd[2];

    if (pipe(pipefd) < 0) {
        perror("pipe error");
        exit(1);
    }

    for (i = 0; i < COUNT; i++) {
        if (write(pipefd[1], buff, BUFFSIZE) < 0) {
            perror("write error");
            exit(1);
        }

        if (read(pipefd[0], buff, BUFFSIZE) != BUFFSIZE) {
            perror("read error");
            exit(1);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
    puts("done");

    return 0;
}
