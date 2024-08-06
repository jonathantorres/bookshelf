#include <stdio.h>

/* A: See code below */
/* B: Because we are iterating down from 64, so the test is done after the first iteration of the
 * loop
 */
/* C: It reverses the bits of x */

long fun_b(unsigned long x)
{
    long val = 0;
    long i;

    for (i = 64; i != 0; i--) {
        val = (val << 1) | (x & 0x1);
        x >>= 1;
    }

    return val;
}

int main(void)
{
    long x = 20;

    printf("%ld\n", fun_b(x));

    return 0;
}
