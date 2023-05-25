#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;

    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }

    printf("\n");
}

void show_short(short v)
{
    show_bytes((byte_pointer)&v, sizeof(short));
}

void show_long(long v)
{
    show_bytes((byte_pointer)&v, sizeof(long));
}

void show_double(double v)
{
    show_bytes((byte_pointer)&v, sizeof(double));
}

int main(void)
{
    double s = 10;
    double l = 100000;
    double d = 2000000.4234;

    show_short(s);
    show_long(l);
    show_double(d);

    return 0;
}
