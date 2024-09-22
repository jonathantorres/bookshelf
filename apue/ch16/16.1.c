#include "apue.h"

typedef union {
    char bytes[4];
    int value;
} record;

int main(void)
{
    record r;
    r.bytes[0] = 0;
    r.bytes[1] = 1;
    r.bytes[2] = 0;
    r.bytes[3] = 0;

    if (r.value == 256) {
        puts("little-endian");
    } else {
        puts("big-endian");
    }

    return 0;
}
