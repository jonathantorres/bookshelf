#include "apue.h"
#include <limits.h>
#include <sys/resource.h>

/*
 * If OPEN_MAX is indeterminate, we're not
 * guaranteed that this is adequate.
 */
#define OPEN_MAX_GUESS 256

long open_max(void)
{
    long openmax;
    struct rlimit rl;

    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX) {
        if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
            err_sys("can't get file limit");
        }
        if (rl.rlim_max == RLIM_INFINITY) {
            openmax = OPEN_MAX_GUESS;
        } else {
            openmax = rl.rlim_max;
        }
    }

    return (openmax);
}

int main(void)
{
    printf("open_max = %ld\n", open_max());
    return 0;
}
