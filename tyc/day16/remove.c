#include <stdio.h>

int main(void)
{
    char filename[80];

    printf("Enter the filename to delete: ");
    gets(filename);

    if (remove(filename) == 0) {
        printf("The file %s has been deleted.\n", filename);
    } else {
        fprintf(stderr, "Error deleteing the file %s\n", filename);
    }

    return 0;
}
