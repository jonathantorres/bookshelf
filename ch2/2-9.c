#include <stdio.h>

int bitcount(unsigned int x);

int main(void)
{
    int n = 75;
    printf("num of 1's in %d = %d\n", n, bitcount(n));
    return 0;
}

int bitcount(unsigned int x)
{
    int b;
    for (b = 0; x != 0; x &= (x-1)) {
        if (x) {
            b++;
        }
    }
    return b;
}
