#include <stdio.h>

unsigned f2u(float x)
{
    return x;
}

int float_le(float x, float y)
{
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    // get the sign bits
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (ux << 1 == 0 && uy << 1 == 0) || (sx > sy) || (sx && sy && ux >= uy) ||
           (!sx && !sy && ux <= uy);
}

int main(void)
{
    printf("%d\n", float_le(0.00, 1.00));
    printf("%d\n", float_le(2.00, 1.00));

    return 0;
}
