#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE 3000000

int main(void)
{
    void *ptr1, *ptr2;

    ptr1 = malloc(BLOCKSIZE);

    if (ptr1 != NULL) {
        printf("\nFirst allocation of %d bytes successful.", BLOCKSIZE);
    } else {
        printf("\nAttempt to allocate %d bytes failed.\n", BLOCKSIZE);
        exit(1);
    }

    ptr2 = malloc(BLOCKSIZE);

    if (ptr2 != NULL) {
        printf("\nSecond allocation of %d bytes successful.\n", BLOCKSIZE);
        exit(0);
    }

    printf("\nSecond attempt to allocate %d bytes failed.", BLOCKSIZE);
    free(ptr1);
    printf("\nFreeing first block.");

    ptr2 = malloc(BLOCKSIZE);

    if (ptr2 != NULL) {
        printf("\nAfter free(), allocation of %d bytes successful.\n", BLOCKSIZE);
    }

    return 0;
}
