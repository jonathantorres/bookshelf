#include <stdio.h>
#include <stdlib.h>

char count, *ptr, *p;

int main(int argc, char const *argv[])
{
    ptr = malloc(35 * sizeof(char));

    if (ptr == NULL) {
        puts("Memory allocation error.");
        return 1;
    }

    p = ptr;

    for (count = 65; count < 91; count++) {
        *p++ = count;
    }

    *p = '\0';

    puts(ptr);
    free(ptr);

    return 0;
}
