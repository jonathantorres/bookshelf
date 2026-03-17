#include "apue.h"
#include <errno.h>

int main(void)
{
    int pid = fork();

    if (pid < 0) {
        err_quit("fork error: %s", strerror(errno));
    } else if (pid == 0) {
        // child
        if (setsid() < 0) {
            err_quit("setsid error: %s", strerror(errno));
        }

        sleep(10);
        exit(EXIT_SUCCESS);
    }

    // parent
    sleep(10);
    printf("done\n");

    return 0;
}
