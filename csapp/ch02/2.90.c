float fpwr2(int x)
{
    /* result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < 2 - pow(2, 7) - 23) {
        /* too small, return 0.0 */
        exp  = 0x0;
        frac = 0x0;
    } else if (x < 2 - pow(2, 7)) {
        /* denormalized result */
        exp  = 0x0;
        frac = 1 << (unsigned)(x - 2 - pow(2, 7) - 23);
    } else if (x < pow(2, 7) - 1 + 1) {
        /* normalized result */
        exp  = pow(2, 7) - 1 + x;
        frac = 0x0;
    } else {
        /* too big return +INF */
        exp  = ~0;
        frac = 0x0;
    }

    /* pack exp and frac into 32 bits */
    u = exp << 23 | frac;

    /* return as float */
    return u2f(u);
}
