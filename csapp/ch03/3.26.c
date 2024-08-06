#include <stdio.h>

/* A: Jump to middle */
/* B: See code below */
/* C: It computes the parity of x */
long fun_a(unsigned long x)
{
    long val = 0;

    while (x != 0) {
        val = val ^ x;
        x >> 1;
    }

    return val & 0x01;
}

int main(void)
{
    unsigned long x = 20;

    printf("%ld\n", fun_a(x));

    return 0;
}
