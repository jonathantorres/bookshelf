#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char source[] = "The source string.";
    char *dest;

    if ((dest = strdup(source)) == NULL) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(1);
    }

    printf("The destination = %s\n", dest);
    return 0;
}
