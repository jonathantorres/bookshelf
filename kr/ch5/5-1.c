#include <ctype.h>
#include <stdio.h>

#define BUFFSIZE 1024

int getint(int *pn);
int getch(void);
void ungetch(int c);

int main(void)
{
    int n, r;
    r = getint(&n);

    if (r > 0) {
        printf("%d\n", n);
    } else if (r == 0) {
        printf("not a number\n");
    } else if (r == EOF) {
        printf("end of file\n");
    } else {
        printf("unknown error!\n");
    }

    return 0;
}

int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) {
        ;
    }

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();

        if (!isdigit(c)) {
            ungetch(c);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }

    return c;
}

char buf[BUFFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
