#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *original_file;
    FILE *destination_file;
    int character;

    if ((original_file = fopen("test.txt", "r")) == NULL) {
        puts("Error reading original file.");
        exit(1);
    }

    if ((destination_file = fopen("test_upper.txt", "w")) == NULL) {
        puts("Error creating destination file.");
        exit(1);
    }

    while ((character = fgetc(original_file)) != EOF) {
        if (character >= 97 && character <= 122) {
            character -= 32;
        }

        fprintf(destination_file, "%c", character);
    }

    fclose(original_file);
    fclose(destination_file);

    return 0;
}
