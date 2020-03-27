#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval tp;
    for (int i = 0; i < 100; ++i) {
        gettimeofday(&tp, NULL);
        printf("secs: %ld\n", tp.tv_sec);
        printf("microsecs: %d\n", tp.tv_usec);
    }
    return 0;
}
