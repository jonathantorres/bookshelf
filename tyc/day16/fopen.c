#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    FILE *fp;
    char ch, filename[40], mode[4];

    while (1) {
        printf("\nEnter a filename: ");
        gets(filename);
        printf("\nEnter a mode (max 3 characters): ");
        gets(mode);

        if ((fp = fopen(filename, mode)) != NULL) {
            printf("\nSuccessful opening %s in mode %s.\n", filename, mode);
            fclose(fp);
            puts("Enter x to exit, any other to continue.");

            if ((ch = getc(stdin)) == 'x') {
                break;
            } else {
                continue;
            }
        } else {
            fprintf(stderr, "\nError opening file %s in mode %s.\n", filename, mode);
            puts("Enter x to exit, any other to try again");

            if ((ch = getc(stdin)) == 'x') {
                break;
            } else {
                continue;
            }
        }
    }

    return 0;
}
