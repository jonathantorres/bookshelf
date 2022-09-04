#include <stdio.h>

double square(double x);

int main(int argc, char const *argv[])
{
    double (*ptr)(double x);

    ptr = square;

    printf("%f\t%f\n", square(6.6), ptr(6.6));
    return 0;
}

double square(double x)
{
    return x * x;
}
