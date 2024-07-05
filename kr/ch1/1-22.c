#include <stdio.h>

#define MAXLINE   1024
#define FOLDLIMIT 20

int getline(char line[], int maxline);
void fold(char line[], int maxline);

int main(void)
{
    int len;
    char line[MAXLINE];

    for (int i = 0; i < MAXLINE; i++) {
        line[i] = 0;
    }

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 0) {
            fold(line, len);
        }
    }

    return 0;
}

void fold(char line[], int maxline)
{
    if (maxline < FOLDLIMIT) {
        printf("%s", line);
        return;
    }

    int fc = 0;

    for (int i = 0; i < maxline; ++i) {
        int c = line[i];

        if (fc >= FOLDLIMIT) {
            fc = 0;
            putchar('\n');
        } else if (c == '\n') {
            fc = 0;
        } else {
            fc++;
        }

        putchar(c);
    }
}

int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
