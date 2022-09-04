#include <stdio.h>

int length, width;
long area;

struct coord {
    int x;
    int y;
};

struct coord my_point;

int main(int argc, char const *argv[])
{
    my_point.x = 12;
    my_point.y = 14;

    printf("\nThe coordinates are: (%d, %d)\n", my_point.x, my_point.y);

    return 0;
}
