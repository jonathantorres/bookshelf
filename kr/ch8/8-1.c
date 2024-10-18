#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error(char *fmt, ...);
void filecopy(int from, int to);

int main(int argc, char *argv[])
{
    int f = -1;

    if (argc == 1) {
        filecopy(0, 1);

        return 0;
    }

    while (--argc > 0) {
        if ((f = open(*++argv, O_RDONLY)) == -1) {
            error("can't open %s", *argv);
            return 1;
        } else {
            filecopy(f, 1);
            close(f);
        }
    }

    return 0;
}

void filecopy(int from, int to)
{
    int n;
    char buf[BUFSIZ];

    while ((n = read(from, buf, BUFSIZ)) > 0) {
        write(to, buf, n);
    }
}

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
