#include <stdio.h>

#define GRID_LENGTH 24

void print_row(char (*p_grid)[GRID_LENGTH]);

int main(void)
{
    char grid[GRID_LENGTH][GRID_LENGTH];
    char (*p_grid)[GRID_LENGTH];

    p_grid = grid;

    // assign values
    for (int i = 0; i < GRID_LENGTH; i++) {
        for (int j = 0; j < GRID_LENGTH; j++) {
            grid[i][j] = 'x';
        }
    }

    for (int i = 0; i < GRID_LENGTH; i++) {
        print_row(p_grid);
    }

    return 0;
}

void print_row(char (*p_grid)[GRID_LENGTH])
{
    for (int i = 0; i < GRID_LENGTH; i++) {
        if (i % 2 == 0) {
            printf("%c", *p_grid[i]);
        } else {
            printf(" ");
        }
    }
    printf("\n");
}
