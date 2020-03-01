#include <stdio.h>
#include <stdarg.h>

void keep_reading(void);
int mscanf(char *fmt, ...);

int main(void)
{
    int a;
    mscanf("-%d", &a);
    printf("%d\n", a);
}

void keep_reading(void)
{
    char c;
    while ((c = getchar()) != '\n' || c != EOF) {

    }
}

int mscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, c;
    int ival, count = 0;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            c = getchar();
            if (c != * p) {
                keep_reading();
                return 0;
            } else {
                continue;
            }
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                count += scanf("%d", & ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                count += scanf("%lf", & dval);
                break;
            case 's':
                sval = va_arg(ap, char * );
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


