#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>

void error(char *, ...);
void filecopy(int from, int to);

int main(int argc, char *argv[])
{
    int f;
    if (argc == 1) {
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((f = open(*++argv, O_RDONLY)) == -1) {
                error("can't open %s", *argv);
                return 1;
            } else {
                filecopy(f, 1);
                close(f);
            }
        }
    }
    return 0;
}

void error(char * fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

void filecopy(int from, int to)
{
    int n;
    char buf[BUFSIZ];
    while ((n = read(from, buf, BUFSIZ)) > 0) {
        write(to, buf, n);
    }
}
