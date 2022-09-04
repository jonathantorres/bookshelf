#include <stdio.h>
#include <stdlib.h>

int random_array[10][10][10];
int a, b, c;

int main(int argc, char const *argv[])
{
    for (a = 0; a < 10; a++) {
        for (b = 0; b < 10; b++) {
            for (c = 0; c < 10; c++) {
                random_array[a][b][c] = rand();
            }
        }
    }

    // display array elements (only 10 at a time)
    for (a = 0; a < 10; a++) {
        for (b = 0; b < 10; b++) {
            for (c = 0; c < 10; c++) {
                printf("\nrandom_array[%d][%d][%d] = ", a, b, c);
                printf("%d", random_array[a][b][c]);
            }
            printf("\nPress Enter to continue, CTRL-C to quit.");
            getchar();
        }
    }

    return 0;
}
