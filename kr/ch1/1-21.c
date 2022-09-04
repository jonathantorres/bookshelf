#include <stdio.h>

#define MAXLINE 1000

void entab(char s[], int len);
int get_line(char s[], int lim);

int main(void)
{
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        entab(line, len);
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

void entab(char s[], int len)
{
    int tab_added = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ' && s[i+1] == ' ' && s[i+2] == ' ' && s[i+3] == ' ') {
            putchar('\t');
            tab_added = 1;
        } else if (s[i] == ' ') {
            if (tab_added == 0) {
                putchar(s[i]);
            }
        } else {
            tab_added = 0;
            putchar(s[i]);
        }
    }
}
