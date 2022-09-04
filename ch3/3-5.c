#include <stdio.h>
#include <limits.h>

void reverse(char s[], int len);
void itob(int n, char s[], int b);

int main(void)
{
    char s1[100];
    char s2[100];
    int n = 530;

    itob(n, s1, 16); // hex
    printf("%d = %s\n", n, s1);
    itob(n, s2, 2); // base 2
    printf("%d = %s\n", n, s2);
    return 0;
}

void itob(int n, char s[], int b)
{
    int i, sign, num;
    i = 0;
    if ((sign = n) < 0) { // record sign
        if (n <= INT_MIN) {
            n++;
        }
        n = -n; // make n positive
    }
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
    reverse(s, i);
}

// reverse: reverse string s in place
void reverse(char s[], int len)
{
    int c, i, j;
    for (i = 0, j = len-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
