#include <stdio.h>

double funct3(int *ap, double b, long c, float *dp)
{
    int a   = *ap;
    float d = *dp;

    if (a < b) {
        return c * d;
    } else {
        return c + 2 * d;
    }
}

int main(void)
{
    int a    = 15;
    double b = 25.0;
    long c   = 25;
    float d  = 125.0;

    printf("%f\n", funct3(&a, b, c, &d));

    return 0;
}
