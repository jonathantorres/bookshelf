#include <stdio.h>
#include <string.h>

int lower(int c);

int main(void)
{
    char *s = "Jonathan Torres";
    printf("%s\n", s);

    for (size_t i = 0; i < strlen(s); i++) {
        putchar(lower(s[i]));
    }

    printf("\n");
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
