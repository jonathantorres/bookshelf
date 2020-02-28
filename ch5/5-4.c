#include <stdio.h>

int strend(char *s, char *t);

int main(void)
{
    char *s1, *s2;
    char s3[] = "first", s4[] = "rst";
    s1 = s3;
    s2 = s4;
    printf("%d\n", strend(s1, s2));
    return 0;
}

int strend(char *s, char *t)
{
    int n = 0;
    for (;*s != '\0'; s++) {
        ;
    }
    for (;*t != '\0'; t++) {
        n++;
    }
    while (n > 0 && (*s-- == *t--)) {
        n--;
    }
    return (n > 0) ? 0 : 1;
}
