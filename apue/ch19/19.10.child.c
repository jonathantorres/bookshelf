#include "apue.h"

void handler(int signum);

int main(void)
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGWINCH, &act, NULL);

    puts("child");

    while (1) {
        //
    }

    return 0;
}

void handler(int signum)
{
    if (signum == SIGWINCH) {
        struct winsize wsize;

        ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&wsize);

        printf("window: %d rows, %d columns\n", wsize.ws_row, wsize.ws_col);
    }
}
