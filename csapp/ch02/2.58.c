#include <stdio.h>

int is_little_endian()
{
    unsigned val      = 0xFF;
    unsigned char *vp = (unsigned char *)&val;

    if (vp[0] == 0xFF) {
        return 1;
    }

    return 0;
}

int main(void)
{
    printf("%d\n", is_little_endian());

    return 0;
}
