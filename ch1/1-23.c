#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim);

int main(void)
{
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        int ignore = 0;
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && i+1 < len && line[i+1] == '/') {
                ignore = 1;
            }
            if (!ignore) {
                putchar(line[i]);
            }
        }
        if (ignore) {
            printf("\n");
        }
    }
    return 0;
}

int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}
