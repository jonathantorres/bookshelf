#include <stdio.h>

int invert(int x, int p, int n);

int main(void)
{
    int x = 200;
    int p = 4;
    int n = 5;

    printf("%d\n", invert(x, p, n));
    return 0;
}

int invert(int x, int p, int n)
{
    int ref = 0;
    ref = ~ref << n;
    ref = ~ref << p;  // mark the exact bits that need negation
    return ((~ref & x) | (ref & ~x));
}
