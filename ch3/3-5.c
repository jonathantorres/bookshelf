#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]);
void itob(int n, char s[], int b);

int main(void)
{
    char s[100];
    long int n = 18237012837;

    itob(n, s, 16);
    printf("%s\n", s);
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

void itob(int n, char s[], int b)
{
    int i, sign, num;
    sign = n;
    n = abs(n); // sets n to be positive
    i = 0;
    do {
        // generate digits in reverse order
        num = n % b;
        if (num < 10) {
          s[i++] = num + '0';
        } else {
          s[i++] = num - 10 + 'a';
        }
    } while ((n /= b) > 0);

    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
