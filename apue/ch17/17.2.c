#include "apue.h"
#include <fcntl.h>
#include <sys/socket.h>

int main(void)
{
    int pid, fd;
    int fdpair[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fdpair) < 0) {
        err_sys("socketpair error");
    }

    TELL_WAIT();
    pid = fork();

    if (pid < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        fd = open("/etc/passwd", O_RDONLY);
        send_fd(fdpair[0], fd);

        WAIT_PARENT();
        lseek(fd, 10, SEEK_SET);
        TELL_PARENT(getppid());

        WAIT_PARENT();
        lseek(fd, 20, SEEK_SET);
        TELL_PARENT(getppid());

        return 0;
    } else {
        fd = recv_fd(fdpair[1], write);
        printf("Parent: got fd: %d, seek: %lld\n", fd, (long long)lseek(fd, 0, SEEK_CUR));
        TELL_CHILD(pid);

        WAIT_CHILD();
        printf("Parent: seek after child changed it: %lld (should be 10)\n",
               (long long)lseek(fd, 0, SEEK_CUR));
        TELL_CHILD(pid);

        WAIT_CHILD();
        printf("Parent: seek after child changed it second time: %lld (should be 20)\n",
               (long long)lseek(fd, 0, SEEK_CUR));

        return 0;
    }
}
