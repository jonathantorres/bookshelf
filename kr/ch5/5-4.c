#include <stdio.h>

int strend(char *s, char *t);

int main(void)
{
    printf("%d\n", strend("first", "rst"));
    printf("%d\n", strend("Jonathan", "test"));
    printf("%d\n", strend("banana", "ab"));

    return 0;
}

int strend(char *s, char *t)
{
    int n = 0;

    for (; *s != '\0'; s++) {
        ;
    }

    for (; *t != '\0'; t++) {
        n++;
    }

    while (n > 0 && (*s-- == *t--)) {
        n--;
    }

    return (n > 0) ? 0 : 1;
}
