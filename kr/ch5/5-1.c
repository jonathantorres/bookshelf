#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000
#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free position in buf

int getint(int *pn);
int getch(void);
void ungetch(int c);

int main(void)
{
    int n;
    int r;
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

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch())) {
        // skip whitespaces
    }
    if (!isdigit(c) && c != EOF && c!= '+' && c != '-') {
        ungetch(c);   // it's not a number
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
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

// get a (possibly pushed back) character
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// push back on input
void ungetch(int c)
{
    if (bufp >= BUFFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
