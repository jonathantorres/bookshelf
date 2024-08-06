#include <stdio.h>

/* A: x is stored in % rbx */
/* B: code changes are below: */
long rfun(unsigned long x)
{
    if (x == 0) {
        return 0;
    }

    unsigned long nx = x >> 2;
    long rv          = rfun(nx);

    return x + rv;
}

int main(void)
{
    long x = 100;

    printf("%ld\n", rfun(x));

    return 0;
}
