#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handler(int signo);
unsigned int snooze(unsigned int secs);
void install_signals();

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: snooze [secs]\n");
        exit(1);
    }

    install_signals();

    unsigned int secs = (unsigned int)atoi(argv[1]);

    snooze(secs);

    return 0;
}

void handler(int signo)
{
    if (signo == SIGINT) {
        // do nothing
        printf("\n");
    }

    return;
}

unsigned int snooze(unsigned int secs)
{
    unsigned int ret = sleep(secs);
    printf("Slept for %u of %u seconds\n", secs - ret, secs);

    return ret;
}

void install_signals()
{
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &act, NULL) < 0) {
        fprintf(stderr, "sigaction() error %s\n", strerror(errno));
        exit(1);
    }
}
