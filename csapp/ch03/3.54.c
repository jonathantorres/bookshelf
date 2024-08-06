#include <stdio.h>

double funct2(double w, int x, float y, long z)
{
    return y * x - w / z;
}

int main(void)
{
    double w = 15.0;
    long x   = 25;
    float y  = 25.0;
    long z   = 125;

    printf("%f\n", funct2(w, x, y, z));

    return 0;
}
