#include <stdio.h>

void reverse(char s[], int len);
void itoa(int n, char s[], int w);

#define MAXLINE 1024

int main(void)
{
    int n1 = 10;
    int n2 = 955;
    int n3 = 298374;

    char s1[MAXLINE];
    char s2[MAXLINE];
    char s3[MAXLINE];

    itoa(n1, s1, 10);
    itoa(n2, s2, 5);
    itoa(n3, s3, 8);

    printf("itoa(%d) = %s\n", n1, s1);
    printf("itoa(%d) = %s\n", n2, s2);
    printf("itoa(%d) = %s\n", n3, s3);

    return 0;
}

void itoa(int n, char s[], int w)
{
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    // generate digits in reverse order
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    for (; i < w; i++) {
        s[i] = '0';
    }

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';

    reverse(s, i);
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
