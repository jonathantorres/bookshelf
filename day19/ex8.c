#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMES 5

int cmp_func(const void *str1, const void *str2);

int main(void)
{
    char *names[MAX_NAMES];
    char current_name[80];

    printf("Enter %d words, pressing Enter after each one\n", MAX_NAMES);

    for (int i = 0; i < MAX_NAMES; i++) {
        fgets(current_name, 80, stdin);
        names[i] = malloc(strlen(current_name) + 1);
        strcpy(names[i], current_name);
    }

    puts("Sorted names");
    qsort(names, MAX_NAMES, sizeof(names[0]), cmp_func);

    for (int i = 0; i < MAX_NAMES; i++) {
        printf("%s", names[i]);
    }

    return 0;
}

int cmp_func(const void *str1, const void *str2)
{
    return strcmp(*(char **)str1, *(char **)str2);
}
