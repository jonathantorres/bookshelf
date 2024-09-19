#include "apue.h"
#include <sys/select.h>
#include <time.h>

// renamed to avoid conflicts
unsigned int my_sleep(unsigned int nsecs)
{
    int n;
    unsigned slept;
    time_t start, end;
    struct timeval tv;

    tv.tv_sec  = nsecs;
    tv.tv_usec = 0;

    time(&start);

    n = select(0, NULL, NULL, NULL, &tv);

    if (n == 0) {
        return 0;
    }

    time(&end);
    slept = end - start;

    if (slept >= nsecs) {
        return 0;
    }

    return (nsecs - slept);
}

int main(void)
{
    printf("Sleeping...");
    fflush(stdout);

    my_sleep(3);

    puts("Done!");

    return 0;
}
