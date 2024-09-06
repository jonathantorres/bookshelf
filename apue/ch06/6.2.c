#include "apue.h"
#include <errno.h>
#include <shadow.h>

// you need the proper privileges to run this program

int main(void)
{
    struct spwd *pass = NULL;

    if ((pass = getspnam("jonathan")) == NULL) {
        err_quit("error retrieving encrypted password: %s", strerror(errno));
    }

    printf("encrypted password: %s\n", pass->sp_pwdp);

    return 0;
}
