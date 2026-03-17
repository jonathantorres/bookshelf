#include "apue.h"
#include <errno.h>
#include <fcntl.h>

// This program unlike cp(1) it just outputs the contents of the first 4096 bytes of the file to
// stdout

int main(int argc, char **argv)
{
    if (argc < 2) {
        err_quit("usage: <file>\n");
    }

    char *file = argv[1];
    char buf[MAXLINE];

    // open and read the source file
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        err_quit("error opening source file: %s\n", strerror(errno));
    }

    int bytes = 0;

    if ((bytes = read(fd, buf, MAXLINE)) == -1) {
        err_quit("error reading the source file: %s\n", strerror(errno));
    }

    for (int i = 0; i < bytes; i++) {
        if (buf[i] != 0) {
            putchar(buf[i]);
        }
    }

    printf("\n");

    return 0;
}
