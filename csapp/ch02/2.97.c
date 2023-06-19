#include <limits.h>
#include <stdio.h>

typedef unsigned float_bits;

float_bits float_i2f(int i)
{
    unsigned sign  = 0x0;
    unsigned exp   = 0x0;
    unsigned frac  = 0x0;
    unsigned left  = 0x0;
    unsigned right = 0x0;
    unsigned t     = 0x0;

    if (i == 0) {
        return i;
    }

    sign = (i & INT_MIN) == INT_MIN;

    if (sign) {
        i = ~i + 1;
    }

    for (right = 1, t = INT_MIN; (t & i) != t; t >>= 1) {
        right++;
    }

    left = (sizeof(int) << 3) - right;
    exp  = left + 127;

    int shift = 0x0;

    if (left <= 23) {
        shift = 23 - left;
        frac  = (i << shift) & 0x7FFFFF;
    } else {
        shift     = left - 23;
        int mask  = ((1 << shift) - 1) & i;
        int half  = 1 << (shift - 1);
        int hide  = 1 << shift;
        int round = mask > half || (mask == half && (i & hide) == hide);
        frac      = (i >> shift) & 0x7FFFFF;

        if (frac == 0x7FFFFF && round == 1) {
            frac = 0;
            exp++;
        } else {
            frac += round;
        }
    }

    return (sign << 31) | (exp << 23) | frac;
}

float u2f(unsigned x)
{
    return *(float *)&x;
}

int main(void)
{
    int x = 342;

    printf("%f\n", u2f(float_i2f(x)));

    return 0;
}
