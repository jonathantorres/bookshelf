#include <stdio.h>

int main(void)
{
    long blanks   = 0;
    long tabs     = 0;
    long newlines = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blanks++;
        } else if (c == '\t') {
            tabs++;
        } else if (c == '\n') {
            newlines++;
        }
    }

    printf("blanks: %ld\ntabs: %ld\nnewlines: %ld\n", blanks, tabs, newlines);
    return 0;
}
