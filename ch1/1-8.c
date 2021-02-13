#include <stdio.h>

int main(void)
{
    int c;
    int blanks = 0;
    int tabs = 0;
    int newlines = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blanks++;
        } else if (c == '\t') {
            tabs++;
        } else if (c == '\n') {
            newlines++;
        }
    }
    printf("b:%d,t:%d,n:%d\n", blanks, tabs, newlines);

    return 0;
}
