#include <stdio.h>
#include <string.h>

#define BUFFSIZE 1024

void strcat2(char *s, char *t);

int main(void)
{
    char a[BUFFSIZE];

    strcpy(a, "Jonathan Torres");
    printf("%s\n", a);

    strcat2(a, " De Jesus");
    printf("%s\n", a);

    return 0;
}

void strcat2(char *s, char *t)
{
    while (*s != '\0') {
        s++;
    }

    while ((*s++ = *t++) != '\0') {
        ;
    }
}
