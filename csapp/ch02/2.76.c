#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0) {
        return NULL;
    }

    size_t bytes = nmemb * size;

    // check for overflow
    if (bytes / nmemb != size) {
        return NULL;
    }

    void *mem = malloc(bytes);

    if (!mem) {
        return NULL;
    }

    memset(mem, 0, bytes);

    return mem;
}

int main(void)
{
    int *num = my_calloc(1, sizeof(int));

    if (!num) {
        printf("allocation failed\n");
        exit(1);
    }

    *num = 100;
    printf("%d\n", *num);
    free(num);

    return 0;
}
