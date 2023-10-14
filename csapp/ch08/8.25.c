#include "csapp.h"
#include <stdio.h>

sigjmp_buf buf;

void handler(int sig)
{
    siglongjmp(buf, 1);
}

char *tfgets(char *s, int size, FILE *stream)
{
    if (!sigsetjmp(buf, 1)) {
        alarm(5);

        if (Signal(SIGALRM, handler) == SIG_ERR) {
            unix_error("set alarm handler error");
        }

        return fgets(s, size, stream);
    }

    return NULL;
}

int main(void)
{
    char buffer[255];
    char *res = tfgets(buffer, 255, stdin);

    if (!res) {
        printf("\nNo input entered\n");

        return 1;
    }

    printf("Input: %s\n", res);

    return 0;
}
