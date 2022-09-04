#include <stdio.h>
#include <stdlib.h>

int file_exists(char *filename);

int main(void)
{
    char ch, source[80];
    int index;
    long count[127];
    FILE *fp;

    fprintf(stdout, "\nEnter source file name: ");
    gets(source);

    if (!file_exists(source)) {
        fprintf(stderr, "\n%s does not exist\n", source);
        exit(1);
    }

    if ((fp = fopen(source, "rb")) == NULL) {
        fprintf(stderr, "\nError opening %s", source);
        exit(1);
    }

    for (index = 31; index < 127; index++) {
        count[index] = 0;
    }

    while (1) {
        ch = fgetc(fp);

        if (feof(fp)) {
            break;
        }

        if (ch > 31 && ch < 127) {
            count[ch]++;
        }
    }

    printf("\nChar\t\tCount\n");

    for (index = 31; index < 127; index++) {
        printf("[%c]\t\t%ld\n", index, count[index]);
    }

    fclose(fp);
    return 0;
}

int file_exists(char *filename)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        return 0;
    } else {
        fclose(fp);
        return 1;
    }
}


