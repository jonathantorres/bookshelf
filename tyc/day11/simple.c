#include <stdio.h>

struct coord {
    int x;
    int y;
} my_point;

struct coord another_one;

int main(int argc, char const *argv[])
{
    my_point.x = 12;
    my_point.y = 14;

    printf("\nThe coordinates are: (%d, %d)\n", my_point.x, my_point.y);

    return 0;
}
