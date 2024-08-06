#include <stdio.h>

/* A: x is in %rdi, n is in %esi, result is in %rax, and mask is in %rdx */
/* B: result = 0 and mask = 1 */
/* C: mask != 0 */
/* D: mask = mask << n & 0xFF */
/* E: result |= x & mask */
/* F: See code below: */
long loop(long x, int n)
{
    long result = 0;
    long mask;

    for (mask = 1; mask != 0; mask = mask << n & 0xFF) {
        result |= x & mask;
    }

    return result;
}

int main(void)
{
    long x = 50;
    int n  = 5;

    printf("%ld\n", loop(x, n));

    return 0;
}
