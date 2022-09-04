#include <stdio.h>
#include <stdlib.h>

#define FILENAME_LENGTH 10

int main(void)
{
    FILE *fp;
    int character;
    char filename[FILENAME_LENGTH];

    while (1) {
        printf("Please enter a filename: ");
        gets(filename);
        // fgets(filename, FILENAME_LENGTH, stdin);

        if ((fp = fopen(filename, "r")) == NULL) {
            fprintf(stderr, "Error opening the file %s\n", filename);
            exit(1);
        }

        while ((character = fgetc(fp)) != EOF) {
            putchar(character);
        }

        fclose(fp);
    }

    return 0;
}
