#include "apue.h"

int fd = 0;

void read_input();

int main()
{
    pid_t pid;
    char slave[MAXLINE];
    struct winsize wsize = {3, 4};

    pid = pty_fork(&fd, slave, MAXLINE, NULL, NULL);

    if (pid == 0) {
        execl("./19.10.child", "./19.10.child", (char *)0);
        return 0;
    } else {
        puts("parent running");

        read_input();

        if (ioctl(fd, TIOCSIG, SIGTERM) == 0) {
            read_input();
        }

        ioctl(fd, TIOCSWINSZ, &wsize);
        read_input();

        return 0;
    }
}

void read_input()
{
    char buf[MAXLINE] = {0};

    sleep(1);

    int n  = read(fd, buf, MAXLINE);
    buf[n] = '\0';

    printf("child: %s\n", buf);
}
