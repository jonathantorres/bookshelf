#include <stdio.h>

int bitcount(int x);

int main(void)
{
    int x = 500;
    printf("%d\n", bitcount(x));
    return 0;
}

int bitcount(int x)
{
    int b;
    for (b = 0; x != 0; x &= (x-1)) {
        b++;
    }
    return b;
}
