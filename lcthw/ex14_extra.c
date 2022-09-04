#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_letters(char *arg, int length);

void print_letters(char *arg, int length)
{
    int i = 0;

    for (i = 0; i < length; i++) {
        char ch = arg[i];

        if (isalpha((int)ch) || isblank((int)ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    int i = 0;

    for (i = 0; i < argc; i++) {
        print_letters(argv[i], strlen(argv[i]));
    }

    return 0;
}
