#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

int main(void)
{
    char buf[BUFSIZE];
    char filename[60];
    FILE *fp;

    puts("Enter name of text file to display.");
    gets(filename);

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    while (!feof(fp)) {
        fgets(buf, BUFSIZE, fp);
        printf("%s", buf);
    }

    fclose(fp);
    return 0;
}
