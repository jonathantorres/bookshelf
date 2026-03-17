#include "apue.h"
#include <errno.h>
#include <sys/utsname.h>

int main(void)
{
    struct utsname info;

    if (uname(&info) < 0) {
        err_quit("uname error: %s", strerror(errno));
    }

    printf("%s\n", info.sysname);
    printf("%s\n", info.nodename);
    printf("%s\n", info.release);
    printf("%s\n", info.version);
    printf("%s\n", info.machine);

    return 0;
}
