unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    int w         = sizeof(int) << 3;
    int hx        = x >> w - 1;
    int hy        = y >> w - 1;
    int high_bits = signed_high_prod(x, y);

    return high_bits + (x & -hy) + (y & -hx);
}
