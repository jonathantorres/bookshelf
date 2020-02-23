#include <stdio.h>

int setbits(int x, int p, int n, int y);

int main(void)
{
    int x = 100;
    int y = 200;
    int p = 2;
    int n = 3;

    printf("%d\n", setbits(x, p, n, y));
    return 0;
}

int setbits(int x, int p, int n, int y)
{
    y = y >> (p-1);      // move the bits starting at pos p to the end
    y = y & ~(~0 << n);  // null all the bits from a pos higher than n
    x = x & (~0 << n);   // null the last n bits
    return (x | y);
}
