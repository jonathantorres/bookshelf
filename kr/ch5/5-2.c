#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getfloat(float *pn);
int getch(void);
void ungetch(int c);

int main(void)
{
    float f;
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

int getfloat(float *pn)
{
    double power;
    int c, sign, exp, esign, bige;
    while (isspace(c = getch())) {
        // skip whitespace
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
            ungetch(sign == 1 ? '+' : '-');
            return 0;
        }
    }
    for (*pn = 0.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
    }
    if (c == '.') {
        c = getchar();
    }
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }
    bige = (c == 'E') ? 1 : 0;
    if (c == 'e' || c == 'E') {
        c = getch();
        esign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-') {
            c = getch();
            if (!isdigit(c)) {
                ungetch(c);
                ungetch(sign == 1 ? '+' : '-');
            }
        } else if (!isdigit(c)) {
            ungetch(c);
            ungetch(bige == 0 ? 'e' : 'E');
        }
        for (exp = 0; isdigit(c); c = getch()) {
            exp = 10 * exp + (c - '0');
        }
        *pn *= (sign / power) * pow(10, esign * exp);
    } else {
        *pn *= (sign / power);
    }
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

