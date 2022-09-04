#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

int comp(const void *s1, const void *s2);

int main(void)
{
    char *data[MAX], buf[80], *ptr, *key, **key1;
    int count;

    printf("Enter %d words, pressing Enter after each.\n", MAX);

    for (count = 0; count < MAX; count++) {
        printf("Word %d: ", count + 1);
        gets(buf);
        data[count] = malloc(strlen(buf) + 1);
        strcpy(data[count], buf);
    }

    qsort(data, MAX, sizeof(data[0]), comp);

    for (count = 0; count < MAX; count++) {
        printf("\n%d: %s", count + 1, data[count]);
    }

    printf("\n\nEnter a search key: ");
    gets(buf);

    key = buf;
    key1 = &key;
    ptr = bsearch(key1, data, MAX, sizeof(data[0]), comp);

    if (ptr != NULL) {
        printf("%s found.\n", buf);
    } else {
        printf("%s not found.\n", buf);
    }

    return 0;
}

int comp(const void *s1, const void *s2)
{
    return (strcmp(*(char **)s1, *(char **)s2));
}
