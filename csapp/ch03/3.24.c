#include <stdio.h>

long loop_while(long a, long b)
{
    long result = 1;

    while (a < b) {
        result = result * (a + b);
        a      = a + 1;
    }

    return result;
}

int main(void)
{
    long a = 20;
    long b = 25;

    printf("%ld\n", loop_while(a, b));

    return 0;
}
