#include <stdio.h>

void printarray_1(int (*ptr)[4]);
void printarray_2(int (*ptr)[4], int n);

int main(void)
{
    int multi[3][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
    };

    int (*ptr)[4];
    int count;
    ptr = multi;

    for (count = 0; count < 3; count++) {
        printarray_1(ptr++);
    }

    puts("\n\nPress Enter...");
    getchar();
    printarray_2(multi, 3);
    puts("");
    return 0;
}

void printarray_1(int (*ptr)[4])
{
    int *p;
    int count;
    p = (int *)ptr;

    for (count = 0; count < 4; count++) {
        printf("\n%d", *p++);
    }
}

void printarray_2(int (*ptr)[4], int n)
{
    int *p;
    int count;
    p = (int *)ptr;

    for (count = 0; count < (4 * n); count++) {
        printf("\n%d", *p++);
    }
}
