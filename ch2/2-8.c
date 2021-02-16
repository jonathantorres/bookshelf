#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);
unsigned int getbits(unsigned int x, int p, int n);
unsigned int setbits(unsigned int x, int p, int n, int y);

int main(void)
{
    unsigned int x = 150;
    int n = 3;
    printf("%u rightrot -> %u\n", x, rightrot(x, n)); // expected result: 210
    return 0;
}

unsigned int rightrot(unsigned int x, int n)
{
    unsigned int b = getbits(x, n-1, n);
    unsigned int nx = x >> n;
    return setbits(nx, 7, n, b);
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
