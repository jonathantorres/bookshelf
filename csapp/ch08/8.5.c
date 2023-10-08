#include <stdio.h>
#include <unistd.h>

unsigned int snooze(unsigned int secs)
{
    unsigned int ret = sleep(secs);
    printf("Slept for %u of %u seconds\n", secs - ret, secs);

    return ret;
}

int main(void)
{
    snooze(5);
    return 0;
}
