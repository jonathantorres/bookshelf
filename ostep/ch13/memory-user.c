#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        puts("Usage: ./memory-user <bytes>");
        exit(1);
    }
    int amount = atoi(argv[1]);
    if (amount == 0) {
        puts("Please provide a number of bytes to allocate");
        exit(1);
    }
    void *data = malloc(amount);
    if (!data) {
        puts("No memory!");
        exit(1);
    }
    memset(data, 0, amount);
    int *data_p = data;
    int i = 0;
    while (1) {
        if (i == amount) {
            i = 0;
            data_p = data;
        }
        printf("data in %p has value %d\n", data_p, *data_p);
        data_p++;
        i++;
    }
    return 0;
}
