#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main(void)
{
    char *msg = "50e-2";
    printf("%f\n", atof(msg));
    return 0;
}

// atof: convert string s to double
double atof(char s[])
{
    double val, power;
    int i, sign, e;

    for (i = 0; isspace(s[i]); i++) {
        // skip whitespace
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if ((s[i] == 'e' || s[i] == 'E') && s[i+1] == '-') {
        i += 2;
        e = 0;
        for (;isdigit(s[i]); i++) {
            e = e * 10 + (s[i] - '0');
        }
        for (i = 0; i <= e; i++) {
            power *= 10.0;
        }
    }
    return sign * val / power;
}
