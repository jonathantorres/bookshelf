#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>

int main(void)
{
    int fd;
    char *p = "unix.socket";
    struct sockaddr_un addr;

    unlink(p);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, p);

    fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (fd < 0) {
        err_sys("socket error");
    }

    if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0) {
        err_sys("bind error");
    }

    struct stat s;

    if (fstat(fd, &s) < 0) {
        err_sys("fstat error");
    }

    printf("device: %lld\n", (long long)s.st_dev);
    printf("inode: %lld\n", (long long)s.st_ino);
    printf("user ID: %lld\n", (long long)s.st_uid);
    printf("group ID: %lld\n", (long long)s.st_gid);
    printf("size: %lld\n", (long long)s.st_size);
    printf("blocks: %lld\n", (long long)s.st_blocks);

    return 0;
}
