#include <stdio.h>

#define BUFSIZE 1024

char *strncpy2(char *d, char *s, int n);
char *strncat2(char *d, char *s, int n);
int strncmp2(char *s, char *t, int n);

int main(void)
{
    char a[BUFSIZE];

    printf("%d\n", strncmp2("john", "johnny", 2));
    printf("%d\n", strncmp2("banana", "here", 4));
    printf("%s\n", strncpy2(a, "Jonathan", 8));
    printf("%s\n", strncat2(a, " Torres", 7));

    return 0;
}

char *strncpy2(char *d, char *s, int n)
{
    int i;
    char *r = d;

    for (i = 0; i < n && *s != '\0'; i++) {
        *d++ = *s++;
    }

    *d = '\0';

    return r;
}

char *strncat2(char *d, char *s, int n)
{
    char *r = d;
    int i;

    while (*d != '\0') {
        d++;
    }

    for (i = 0; *s != '\0' && i < n; i++) {
        *d++ = *s++;
    }

    *d = '\0';

    return r;
}

int strncmp2(char *s, char *t, int n)
{
    int i;

    for (i = 0; i < n && (*s++ == *t++); i++) {
        ;
    }

    if (i == n) {
        return 0;
    }

    return (*--s > *--t) ? 1 : -1;
}
