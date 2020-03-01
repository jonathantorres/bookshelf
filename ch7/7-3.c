#include <stdio.h>
#include <stdarg.h>

void miniprintf(char * fmt, ...);

int main(void)
{
    miniprintf("This is the %c\n", 's');
}

void miniprintf(char * fmt, ...)
{
    va_list ap;
    char * p, * sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar( * p);
            continue;
        }
        switch (*++p) {
            case 'i':
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'o':
                ival = va_arg(ap, int);
                printf("%o", ival);
                break;
            case 'X':
            case 'x':
                ival = va_arg(ap, int);
                printf("%x", ival);
                break;
            case 'u':
                ival = va_arg(ap, int);
                printf("%u", ival);
                break;
            case 'c':
                ival = va_arg(ap, int);
                printf("%c", ival);
                break;
            case 'G':
            case 'g':
            case 'E':
            case 'e':
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++) {
                    putchar(*sval);
                }
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
