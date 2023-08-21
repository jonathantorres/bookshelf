#include <stdio.h>
#include <string.h>

double poly(double a[], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr   = x;

    for (i = 1; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }

    return result;
}

double poly_fast(double a[], double x, long degree)
{
    long i;
    long limit     = degree - 5;
    double xpwr1   = x;
    double xpwr2   = x * x;
    double xpwr3   = x * x * x;
    double xpwr4   = x * x * x * x;
    double xpwr5   = x * x * x * x * x;
    double x_5     = x * x * x * x * x;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;

    for (i = 1; i <= limit; i += 5) {
        result0 += a[i] * xpwr1;
        result1 += a[i + 1] * xpwr2;
        result2 += a[i + 2] * xpwr3;
        result3 += a[i + 3] * xpwr4;
        result4 += a[i + 4] * xpwr5;

        xpwr1 = x_5 * xpwr1;
        xpwr2 = x_5 * xpwr2;
        xpwr3 = x_5 * xpwr3;
        xpwr4 = x_5 * xpwr4;
        xpwr5 = x_5 * xpwr5;
    }

    for (; i < degree; i++) {
        result0 += a[i] * xpwr1;
        xpwr1 = x * xpwr1;
    }

    return result0 + result1 + result2 + result3 + result4;
}

int main(void)
{
    int n = 16;
    double a[n];
    memset(a, 0, sizeof(double) * n);

    for (size_t i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    double x = poly(a, 1.3, n);
    double y = poly_fast(a, 1.3, n);

    printf("%lf <-> %lf\n", x, y);

    return 0;
}
