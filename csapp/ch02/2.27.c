int uadd_ok(unsigned x, unsigned y) {
    // determine whether arguments can be added without overflow
    return (x + y) < x;
}
