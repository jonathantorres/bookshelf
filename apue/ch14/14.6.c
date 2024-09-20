#include "apue.h"
#include <sys/select.h>

void sleep_us(unsigned int nusecs)
{
    struct timeval tval;

    tval.tv_sec  = nusecs / 1000000;
    tval.tv_usec = nusecs % 1000000;

    select(0, NULL, NULL, NULL, &tval);
}

int main(void)
{
    // sleep for 2 one seconds
    sleep_us(2000000);

    return 0;
}
