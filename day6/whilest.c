#include <stdio.h>

int count;

int main(int argc, char const *argv[])
{
    count = 1;

    while (count <= 20) {
        printf("%d\n", count);
        count++;
    }

    return 0;
}
