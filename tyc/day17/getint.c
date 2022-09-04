#include <stdio.h>
#include <ctype.h>

int get_int(void);

int main(int argc, char const *argv[])
{
    int x;

    x = get_int();

    printf("You entered %d.\n", x);
    return 0;
}

int get_int(void)
{
    int ch, i, sign = 1;

    while (isspace(ch = getchar())) {
        ;
    }

    if (ch != '-' && ch != '+' && !isdigit(ch) && ch != EOF) {
        ungetc(ch, stdin);
        return 0;
    }

    if (ch == '-') {
        sign = -1;
    }

    if (ch == '+' || ch == '-') {
        ch = getchar();
    }

    for (i = 0; isdigit(ch); ch = getchar()) {
        i = 10 * i + (ch - '0');
    }

    i *= sign;

    if (ch != EOF) {
        ungetc(ch, stdin);
    }

    return i;
}
