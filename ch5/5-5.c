#include <stdio.h>

char *strn_cpy(char *d, char *s, int n);
char *strn_cat(char *d, char *s, int n);
int strn_cmp(char *s, char *t, int n);

int main(void)
{
    char *s1 = "john";
    char *s2 = "johnny";
    char s3[20];

    printf("%d\n", strn_cmp(s1, s2, 2));
    printf("%s\n", strn_cpy(s3, s1, 20));
    printf("%s\n", strn_cat(s3, s2, 20));
    return 0;
}

char *strn_cpy(char *d, char *s, int n)
{
    int i;
    char *r;
    r = d;
    for (i = 0; i < n && *s != '\0'; i++) {
        *d++ = *s++;
    }
    *d = '\0';
    return r;
}

char *strn_cat(char *d, char *s, int n)
{
    char *r;
    int i;
    r = d;
    for (; *d != '\0'; d++) {
        ;
    }
    for (i = 0; *s != '\0' && i < n; i++) {
        *d++ = *s++;
    }
    *d = '\0';
    return r;
}

int strn_cmp(char *s, char *t, int n)
{
    int i;
    for (i = 0; i < n && (*s++ == *t++); i++) {
        ;
    }
    if (i == n) {
        return 0;
    } else {
        return (*(s-1) > *(t-1)) ? 1 : -1;
    }
}
