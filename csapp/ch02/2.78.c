#include <limits.h>
#include <stdio.h>

int divide_power2(int x, int k)
{
    int bias = 0;

    ((x & INT_MIN) && (bias = (1 << k) - 1));

    return (x + bias) >> k;
}

int main(void)
{
    printf("%d\n", divide_power2(100, 1));
    printf("%d\n", divide_power2(-12340, 4));

    return 0;
}
