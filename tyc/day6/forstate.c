#include <stdio.h>

int count;

int main(int argc, char const *argv[])
{
    for (count = 1; count <= 20; count++) {
        printf("%d\n", count);
    }

    return 0;
}
