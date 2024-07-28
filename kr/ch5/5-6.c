#include <stdio.h>
#include <string.h>

#define BUFSIZE 1024
#define NSIZE   64

void itoa(int n, char *s);
int strindex(char *s, char *t);
int getline(char *s, int lim);
void reverse(char *s);

int main(void)
{
    char msg[BUFSIZE];
    getline(msg, BUFSIZE);
    reverse(msg);
    printf("%s\n", msg);

    char n[NSIZE];
    itoa(1800, n);
    printf("%s\n", n);

    printf("%d\n", strindex("Jonathan", "han")); // expected 5

    return 0;
}

int getline(char *s, int lim)
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
    int sign, rem;
    char *t = s;
    sign    = n;

    do {
        rem = n % 10;
        if (rem < 0) {
            rem = -rem;
        }
        *s++ = rem + '0';
    } while ((n /= 10) != 0);

    if (sign < 0) {
        *s++ = '-';
    }

    *s = '\0';

    reverse(t);
}

int strindex(char *s, char *t)
{
    int i;
    char *sp;

    for (i = 0; *s != '\0'; i++, s++) {
        for (sp = s; *t != '\0' && *sp == *t; t++, sp++) {
            ;
        }

        if (*t == '\0') {
            return i;
        }
    }

    return -1;
}

void reverse(char *s)
{
    int c;
    char *t;

    for (t = s + (strlen(s) - 1); s < t; s++, t--) {
        c  = *s;
        *s = *t;
        *t = c;
    }
}
