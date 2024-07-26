#include <stdio.h>

void itoa(int n, char s[]);
void reverse(char s[], int len);

#define MAXLINE 1024

int main(void)
{
    char a[MAXLINE];
    char b[MAXLINE];
    char c[MAXLINE];

    itoa(100, a);
    itoa(2384, b);
    itoa(-250, c);

    printf("%s\n", a);
    printf("%s\n", b);
    printf("%s\n", c);

    return 0;
}

void itoa(int n, char s[])
{
    static int i    = 0;
    static int sign = 0;

    if (i == 0 && n < 0) {
        sign = n;
        n    = -n;
    }

    s[i++] = n % 10 + '0';

    if ((n /= 10) == 0) {
        if (sign < 0) {
            s[i++] = '-';
        }

        s[i] = '\0';

        reverse(s, i);

        sign = 0;
        i    = 0;
        return;
    }

    itoa(n, s);
}

void reverse(char s[], int len)
{
    int c, i, j;

    for (i = 0, j = len - 1; i < j; i++, j--) {
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
