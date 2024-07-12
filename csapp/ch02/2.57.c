#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;

    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }

    printf("\n");
}

void show_short(short x)
{
    show_bytes((byte_pointer)&x, sizeof(short));
}

void show_long(long x)
{
    show_bytes((byte_pointer)&x, sizeof(long));
}

void show_double(double x)
{
    show_bytes((byte_pointer)&x, sizeof(double));
}

int main(void)
{
    short a  = 55;
    long b   = 5080;
    double f = 638.832;

    show_short(a);
    show_long(b);
    show_double(f);

    return 0;
}
