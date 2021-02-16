#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);
unsigned int getbits(unsigned int x, int p, int n);
unsigned int setbits(unsigned int x, int p, int n, int y);

int main(void)
{
    unsigned int x = 225;
    int p = 4;
    int n = 2;
    printf("%u inverted = %u\n", x, invert(x, p, n));
    return 0;
}

// returns x with the n bits that begin at position p
// inverted, leaving the others unchanged
unsigned int invert(unsigned int x, int p, int n)
{
    unsigned b = getbits(x, p, n);
    return setbits(x, p, n, ~b);
}

// getbits: get n bits from position p
unsigned int getbits(unsigned int x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned int setbits(unsigned int x, int p, int n, int y)
{
    unsigned int ry = getbits(y, n-1, n);
    ry = ry << (p+1-n);
    unsigned int m = ((1 << n)-1) << (p+1-n);
    return x ^ ((x ^ ry) & m);
}
