#include <stdio.h>

int main(void)
{
    int x = 0xFF000000;

    int a = !!x;
    int b = !!(x ^ ~0);
    int c = !!(x & 0xFF);
    int d = !!(((x >> ((sizeof(int) - 1) << 3)) | ~0xFF) ^ ~0);

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
    printf("%d\n", d);

    return 0;
}
