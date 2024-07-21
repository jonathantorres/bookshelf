#include <ctype.h>
#include <stdio.h>

double atof(char s[]);

int main(void)
{
    printf("%f\n", atof("50e-2"));
    printf("%f\n", atof("50e2"));
    printf("%f\n", atof("230.27324"));
    printf("%f\n", atof("362"));

    return 0;
}

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

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        sign = (s[++i] == '-') ? -1 : 1;

        if (s[i] == '+' || s[i] == '-') {
            i++;
        }

        for (e = 0; isdigit(s[i]); i++) {
            e = e * 10 + (s[i] - '0');
        }

        if (sign == 1) {
            for (i = 0; i <= e; i++) {
                val *= 10;
            }
        } else {
            for (i = 0; i <= e; i++) {
                val /= 10;
            }
        }
    }

    return val;
}
