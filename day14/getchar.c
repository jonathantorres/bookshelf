#include <stdio.h>

int main(int argc, char const *argv[])
{
    int ch;

    while ((ch = getchar()) != '\n') {
        putchar(ch);
    }

    return 0;
}
