long decode(long x, long y, long z)
{
    y -= z;
    return (y << 63 >> 63) ^ (x * y);
}
