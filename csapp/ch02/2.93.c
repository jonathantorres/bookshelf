#include <stdio.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits f)
{
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    // check if NaN
    if (exp == 0xFF && frac != 0) {
        return f;
    }

    return (0 << 31) | (exp << 23) | frac;
}

float u2f(unsigned x)
{
    return *(float *)&x;
}

unsigned f2u(float f)
{
    return *(unsigned *)&f;
}

int main(void)
{
    float f = -100.0;

    printf("%f\n", u2f(float_absval(f2u(f))));

    return 0;
}
