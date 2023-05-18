int div16(int x)
{
    return x + (x >> 31 & 0xF) >> 4;
}
