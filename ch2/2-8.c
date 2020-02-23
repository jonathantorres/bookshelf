#include <stdio.h>

int rightrot(int x, int n);

int main(void)
{
    int x = 500;
    int n = 2;
    printf("%d\n", rightrot(x, n));
    return 0;
}

int rightrot(int x, int n)
{
    int end = 0;
    end = ~(~end << n);
    end = x & end;
    end = end << (8 * sizeof(x) - n);
    return ((x >> n) | end);
}
