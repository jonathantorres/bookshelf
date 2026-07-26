#include "apue.h"

void my_setbuf(FILE *restrict fp, char *restrict buf);

int main(void)
{
    char buf[MAXLINE];

    my_setbuf(stdout, buf);

    fprintf(stdout, "stream with a new buffer\n");

    return 0;
}

void my_setbuf(FILE *restrict fp, char *restrict buf)
{
    int bufsize = sizeof(buf);

    if (bufsize < BUFSIZ) {
        bufsize = BUFSIZ;
    }

    if (setvbuf(fp, buf, _IOLBF, bufsize) < 0) {
        err_quit("error setting the buffer");
    }
}
