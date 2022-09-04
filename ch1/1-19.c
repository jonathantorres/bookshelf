#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim);
void reverse(char s[], char rev[], int lim);
void reset(char s[]);

int main(void)
{
    char line[MAXLINE];
    char rev[MAXLINE];
    char *revp = &rev[1]; // strip the leading newline
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line, rev, len);
        printf("%s\n", revp);
    }

    return 0;
}

void reverse(char s[], char rev[], int lim)
{
    reset(rev);
    for (int i = lim-1, j = 0; i >= 0; i--, j++) {
        rev[j] = s[i];
    }
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

void reset(char s[])
{
    for (int i = 0; i < MAXLINE-1; i++) {
        s[i] = '\0';
    }
}
