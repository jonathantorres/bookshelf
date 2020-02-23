#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[], int m);

int main(void)
{
    int n = 324;
    int m = 5;
    char s[25];

    itoa(n, s, m);
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

void itoa(int n, char s[], int m)
{
    int i, sign;
    sign = n;
    n = abs(n); // sets n to be positive
    i = 0;
    // generate digits in reverse order
    do {
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it
    if (sign < 0) {
        s[i++] = '-';
    }
    // add padding
    for (;i < m; i++) {
        s[i] = ' ';
    }
    s[i+1] = '\0';
    reverse(s);
}
