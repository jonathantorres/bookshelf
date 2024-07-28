#include <ctype.h>
#include <math.h>
#include <stdio.h>

#define BUFFSIZE 1024

int getfloat(double *pf);
int getch(void);
void ungetch(int c);

int main(void)
{
    double f;
    int r;
    r = getfloat(&f);

    if (r > 0) {
        printf("%f\n", f);
    } else if (r == 0) {
        printf("not a number\n");
    } else if (r == EOF) {
        printf("end of file\n");
    } else {
        printf("unknown error!\n");
    }

    return 0;
}

int getfloat(double *pf)
{
    double power;
    int c, sign;

    while (isspace(c = getch())) {
        ;
    }

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }

    for (*pf = 0.0; isdigit(c); c = getch()) {
        *pf = 10.0 * *pf + (c - '0');
    }

    if (c == '.') {
        c = getchar();
    }

    for (power = 1.0; isdigit(c); c = getch()) {
        *pf = 10.0 * *pf + (c - '0');
        power *= 10.0;
    }

    *pf *= (sign / power);

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
