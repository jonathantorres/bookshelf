#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    int character;
    int num_of_characters = 0;

    if ((fp = fopen("test.txt", "r")) == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    while ((character = fgetc(fp)) != EOF) {
        num_of_characters++;
    }

    fprintf(stdout, "Total number of characters is: %d\n", num_of_characters);
    fclose(fp);

    return 0;
}
