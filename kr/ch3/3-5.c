#include <stdio.h>

void reverse(char s[], int len);
void itob(int n, char s[], int b);

#define MAXLINE 1024

int main(void)
{
    int n = 955;

    char s1[MAXLINE];
    char s2[MAXLINE];
    char s3[MAXLINE];

    itob(n, s1, 10);
    itob(n, s2, 2);
    itob(n, s3, 16);

    printf("itob(%d, %d) = %s\n", n, 10, s1);
    printf("itob(%d, %d) = %s\n", n, 2, s2);
    printf("itob(%d, %d) = %s\n", n, 16, s3);

    return 0;
}

void itob(int n, char s[], int b)
{
    int i, sign, rem;

    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    // generate digits in reverse order
    do {
        rem = n % b;

        if (rem < 10) {
            s[i++] = rem + '0';
        } else {
            s[i++] = rem - 10 + 'a';
        }
    } while ((n /= b) > 0);

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
