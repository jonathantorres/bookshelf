#include <stdio.h>

long loop_while2(long a, long b)
{
    long result = b;

    while (b > 0) {
        result = result * a;
        b      = b - a;
    }

    return result;
}

int main(void)
{
    long a = 20;
    long b = 25;

    printf("%ld\n", loop_while2(a, b));

    return 0;
}
