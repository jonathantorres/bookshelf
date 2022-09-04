#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]);
void itoa_r(int n, char s[]);

int main(void)
{
    int n = 324;
    char s[25];

    itoa_r(n, s);
    printf("%d = %s\n", n, s);
    return 0;
}

// reverse: reverse string s in place
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// itoa: convert n to characters in s
void itoa_r(int n, char s[])
{
    static int i = 0;
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    if ((n / 10) > 0) {
        itoa_r((n/10), s);
    }
    s[i++] = (n % 10) + '0';
    s[i] = '\0';
}
