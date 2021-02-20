#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char *s);
int strindex(char *s, char *t);
int get_line(char *s, int lim);
void reverse(char *s);

int main(void)
{
    int lim = 100;
    char msg[lim];
    get_line(msg, lim);
    reverse(msg);
    printf("%s\n", msg);

    char n[20];
    itoa(1800, n);
    printf("%s\n", n);

    char *s1 = "Jonathan";
    char *s2 = "han";
    printf("%d\n", strindex(s1, s2)); // expected 5
    return 0;
}

void reverse(char *s)
{
    int c;
    char *t;
    for (t = s + (strlen(s)-1); s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}

int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return i;
}

void itoa(int n, char *s)
{
    char *r = s;
    int sign;
    if ((sign = n) < 0) { // record sign
        if (n <= INT_MIN) {
            n++;
        }
        n = -n; // make n positive
    }
    // generate digits in reverse order
    do {
        *s++ = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it

    if (sign < 0) {
        *s++ = '-';
    }
    *s = '\0';
    reverse(r);
}

int strindex(char *s, char *t)
{
    int i, j;
    char *tp;
    char *sp1;
    char *sp2;
    for (i = 0, sp1 = s; *sp1 != '\0'; i++, sp1++) {
        for (j = 0, sp2 = sp1, tp = t; *tp != '\0' && *sp2 == *tp; j++, tp++, sp2++) {
            ;
        }
        if (j > 0 && *tp == '\0') {
            return i;
        }
    }
    return -1;
}
