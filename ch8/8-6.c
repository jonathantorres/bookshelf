#include <stdio.h>
#include <stdlib.h>

void *my_calloc(size_t nmemb, size_t size);

int main(void)
{
    char *p;
    int i;
    p = (char *)my_calloc(10, sizeof(char));
    for (i = 0; i < 10; ++i) {
        printf("%d\n", *(p+i));
    }
    free(p);
    return 0;
}

void *my_calloc(size_t nmemb, size_t size)
{
    char *p = malloc(nmemb * size);
    if (p == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < nmemb * size; ++i) {
        *(p+i) = 0;
    }
    return p;
}
