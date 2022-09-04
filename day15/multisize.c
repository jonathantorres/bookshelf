#include <stdio.h>

int multi[2][4];

int main(int argc, char const *argv[])
{
    printf("\nThe size of multi = %u", sizeof(multi));
    printf("\nThe size of multi[0] = %u", sizeof(multi[0]));
    printf("\nThe size of multi[0][0] = %u\n", sizeof(multi[0][0]));

    return 0;
}
