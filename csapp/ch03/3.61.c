long cread_alt(long *xp)
{
    long z  = 0;
    long *v = xp;

    if (!xp) {
        v = &z;
    }

    return *v;
}
