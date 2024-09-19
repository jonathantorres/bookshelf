#include "apue.h"
#include <pthread.h>

pthread_mutex_t plock = PTHREAD_MUTEX_INITIALIZER;

int putenv_r(char *string);

int main(void)
{
    putenv_r("FOO=bar");

    system("env");

    return 0;
}

int putenv_r(char *string)
{
    sigset_t new;
    sigset_t old;

    if (sigfillset(&new) < 0) {
        err_quit("sigfillset error");
    }

    if (sigprocmask(SIG_BLOCK, &new, &old) < 0) {
        err_quit("sigprocmask error");
    }

    int err = pthread_mutex_lock(&plock);

    if (err != 0) {
        err_exit(err, "error locking mutex");
    }

    int rc = putenv(string);
    err    = pthread_mutex_unlock(&plock);

    if (err != 0) {
        err_exit(err, "error unlocking mutex");
    }

    if (sigprocmask(SIG_SETMASK, &old, NULL) < 0) {
        err_quit("sigprocmask error");
    }

    return rc;
}
