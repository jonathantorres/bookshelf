#include <stdio.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned rest = f & 0x7FFFFFFF;

    // check if NaN
    if (exp == 0xFF && frac != 0) {
        return f;
    }

    int add = (frac & 0x03) == 0x03;

    if (exp == 0x00) {
        frac >>= 1;
        frac += add;
    } else if (exp == 0x1) {
        rest >>= 1;
        rest += add;
        exp  = rest >> 23 & 0xFF;
        frac = rest & 0x7FFFFF;
    } else {
        exp -= 1;
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
    float f = 200.0;

    printf("%f\n", u2f(float_half(f2u(f))));

    return 0;
}
