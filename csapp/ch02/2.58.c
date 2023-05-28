#include <stdio.h>

int is_little_endian()
{
    int val           = 0xFF;
    unsigned char *vp = (unsigned char *)&val;

    if (vp[0] == 0xFF) {
        return 1; // is little endian
    }

    return 0;
}

int main(void)
{
    printf("%d\n", is_little_endian());

    return 0;
}
