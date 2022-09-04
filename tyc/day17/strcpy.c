#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char source[] = "The source string";
    char dest1[80];
    char *dest2, *dest3;

    printf("source: %s\n", source);
    strcpy(dest1, source);
    printf("dest1: %s\n", dest1);

    dest2 = (char *)malloc(strlen(source) + 1);
    strcpy(dest2, source);
    printf("dest2: %s\n", dest2);

    // Don't do this!!!
    // strcpy(dest3, source);
    return 0;
}
