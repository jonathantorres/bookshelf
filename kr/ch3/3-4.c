#include <limits.h>
#include <stdio.h>

void reverse(char s[], int len);
void itoa(int n, char s[]);

#define MAXLINE 1024

int main(void)
{
    int n1 = 10;
    int n2 = 955;
    int n3 = INT_MIN;

    char s1[MAXLINE];
    char s2[MAXLINE];
    char s3[MAXLINE];

    itoa(n1, s1);
    itoa(n2, s2);
    itoa(n3, s3);

    printf("itoa(%d) = %s\n", n1, s1);
    printf("itoa(%d) = %s\n", n2, s2);
    printf("itoa(%d) = %s\n", n3, s3);

    return 0;
}

void itoa(int n, char s[])
{
    int i, sign, rem;
    sign = n;
    i    = 0;

    // generate digits in reverse order
    do {
        rem = n % 10;
        if (rem < 0) {
            rem = -rem;
        }
        s[i++] = rem + '0';   // get next digit
    } while ((n /= 10) != 0); // delete it

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
