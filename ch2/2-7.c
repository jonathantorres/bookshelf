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

// TODO: there's a bug here, revise ex. 2-6
// to reproduct, try invert() with these values:
// unsigned int x = 150;
// int p = 2;
// int n = 3;
unsigned int setbits(unsigned int x, int p, int n, int y)
{
    unsigned int ry = getbits(y, p, n);
    int xa = x & (~0 << n);
    ry = ry << (p+1-n);
    return xa | ry;
}
