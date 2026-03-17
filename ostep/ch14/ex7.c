#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100 * sizeof(int));
    free(data[50]);
    printf("data[100] is: %d\n", data[100]);
    return 0;
}
