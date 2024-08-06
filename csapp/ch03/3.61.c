#include <stdio.h>

long cread_alt(long *xp)
{
    long z  = 0;
    long *v = xp;

    if (!xp) {
        v = &z;
    }

    return *v;
}

int main(void)
{
    long x = 25;

    printf("%ld\n", cread_alt(&x));

    return 0;
}
