#include <stdarg.h>
#include <stdio.h>

int mscanf(char *fmt, ...);
void keep_reading(void);

int main(void)
{
    int i;
    printf("Enter a number: ");
    mscanf("%d\n", &i);
    printf("%d\n", i);

    double f;
    printf("Enter a floating point number: ");
    mscanf("%f\n", &f);
    printf("%f\n", f);

    char s[100];
    printf("Enter a word: ");
    mscanf("%s\n", &s);
    printf("%s\n", s);
}

int mscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, c;
    int *ival;
    int count = 0;
    double *dval;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            c = getchar();

            if (c != *p) {
                keep_reading();
                return 0;
            } else {
                continue;
            }
        }

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int *);
                count += scanf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double *);
                count += scanf("%lf", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                count += scanf("%s", sval);
                break;
            default:
                printf("wrong format!");
                return 0;
        }
    }

    va_end(ap);

    return count;
}

void keep_reading(void)
{
    char c;

    while ((c = getchar()) != '\n' || c != EOF) {
        ;
    }
}
