#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char search[] = "printf";
    char buffer[128];
    int line_number = 0;
    FILE *fp;

    fp = fopen("atof.c", "r");

    if (fp == NULL) {
        puts("Could not read file.");
        exit(1);
    }

    while (fgets(buffer, 128, fp) != NULL) {
        line_number++;

        if (strstr(buffer, search) != NULL) {
            printf("%s was found on line %d\n", search, line_number);
        }
    }

    return 0;
}
