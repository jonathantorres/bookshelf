#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    char filename[80];

    printf("Enter filename: ");
    gets(filename);

    if ((fp = fopen(filename, "r")) == NULL) {
        perror("you goofed!");
        printf("errno = %d\n", errno);
        exit(1);
    }

    puts("File opened for reading.");
    fclose(fp);
    return 0;
}
