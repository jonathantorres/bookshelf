// 1-27 - Describe how to test whether a given set of tickets establishes sufficient coverage in
// the Lotto problem of lotto. Write a program to find good ticket sets.
#include <stdio.h>

int main(void)
{
    int max_num = 49;
    int min_num = 1;
    int total_nums = 6;
    int winning[6] = { 11, 23, 34, 21, 30, 40 };
    int sets[4][6] = {
        { 45, 16, 11, 9, 6, 22 },
        { 17, 8, 2, 9, 11, 23 },
        { 10, 30, 20, 29, 31, 21 },
        { 4, 12, 44, 19, 3, 40 },
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%d\n", sets[i][j]);
        }
    }

    return 0;
}
