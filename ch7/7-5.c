#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

double atof(char s[]);

int main(void)
{
    double sum, atof(char s[]);
    char s[MAXLINE];
    sum = 0;
    while (scanf("%s", s) != EOF) {
        printf("\t%g\n", sum += atof(s));
    }
    return 0;
}

double atof(char s[])
{
    double val, power;
    int i, sign;
    for (i = 0; s[i] == ' '; i++) {

    }
    sign = (s[i] == '-') ? -1 : 1;
    if ((s[i] == '+') || (s[i] == '-')) {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return (sign * val / power);
}
