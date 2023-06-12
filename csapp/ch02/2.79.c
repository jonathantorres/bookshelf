#include <limits.h>
#include <stdio.h>

int mul3div4(int x)
{
    int r    = (x << 2) - x;
    int bias = 0;

    (r & INT_MIN && (bias = (1 << 2) - 1));

    return (r + bias) >> 2;
}

int main(void)
{
    printf("%d\n", mul3div4(100));
    printf("%d\n", mul3div4(1000));
    printf("%d\n", mul3div4(-5000));

    return 0;
}
