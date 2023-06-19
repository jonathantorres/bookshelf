#include <stdio.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    // check if NaN
    if (exp == 0xFF && frac != 0) {
        return f;
    }

    if (exp == 0x0) {
        frac <<= 1;
    } else if (exp == 0xFF - 1) {
        exp  = 0xFF;
        frac = 0x0;
    } else {
        exp += 1;
    }

    return (sign << 31) | (exp << 23) | frac;
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
    float f = 55.0;

    printf("%f\n", u2f(float_twice(f2u(f))));

    return 0;
}
