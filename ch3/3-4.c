#include <stdio.h>
#include <limits.h>

void reverse(char s[], int len);
void itoa(int n, char s[]);
void itoa2(int n, char s[]);

#define MAXLEN 25

int main(void)
{
    char s1[MAXLEN];
    int n1 = 10;
    char s2[MAXLEN];
    int n2 = 955;
    char s3[MAXLEN];
    int n3 = INT_MIN;
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
    int i, sign;
    if ((sign = n) < 0) { // record sign
        if (n <= INT_MIN) {
            n++;
        }
        n = -n; // make n positive
    }
    i = 0;
    // generate digits in reverse order
    do {
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it

    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s, i);
}

void itoa2(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0) { // record sign
        n = -n; // make n positive
    }
    i = 0;
    // generate digits in reverse order
    do {
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it

    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s, i);
}

void reverse(char s[], int len)
{
    int c, i, j;
    for (i = 0, j = len-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
