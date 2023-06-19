#include <stdio.h>

typedef unsigned float_bits;

int float_f2i(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp  = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned bias = 0x7F;
    unsigned e2   = 0x0;
    unsigned mant = 0x0;

    /* overflow */
    if (exp >= 31 + bias || exp == 0xFF) {
        return 0x80000000;
    }

    /* less than one */
    if (exp < bias) {
        return 0;
    }

    mant    = frac | 0x800000;
    e2      = exp - bias;
    int res = 0;

    if (e2 > 23) {
        res = mant << (e2 - 23);
    }

    res = mant >> (23 - e2);

    return sign ? -res : res;
}

unsigned f2u(float f)
{
    return *(unsigned *)&f;
}

int main(void)
{
    float f = 133.71;

    printf("%d\n", float_f2i(f2u(f)));

    return 0;
}
