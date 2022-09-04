#include <stdio.h>

int main(int argc, char const *argv[])
{
    int count = 0;

    printf("\nOutside the block, count = %d", count);

    {
        int count = 999;

        printf("\nWithin the block, count = %d", count);
    }

    printf("\nOutside the block again, count = %d\n", count);

    return 0;
}
