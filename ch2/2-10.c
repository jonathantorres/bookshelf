#include <stdio.h>

int lower(int c);

int main(void)
{
    char s[9] = "JonaTHan";
    printf("%s\n", s);
    for (int i = 0; i < 8; i++) {
        putchar(lower(s[i]));
    }
    puts("");
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
