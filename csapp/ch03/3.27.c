#include <stdio.h>

long fact_for_gd_goto(long n)
{
    long i      = 2;
    long result = 1;

    if (n <= 1) {
        goto done;
    }

loop:
    result *= i;
    i++;

    if (i <= n) {
        goto loop;
    }

done:
    return result;
}

int main(void)
{
    long n = 5;

    printf("%ld\n", fact_for_gd_goto(n));

    return 0;
}
