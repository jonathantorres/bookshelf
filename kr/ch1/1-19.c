#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char s[], int size);

int main(void)
{
    int len;
    char line[MAXLINE];

    for (int i = 0; i < MAXLINE; i++) {
        line[i] = 0;
    }

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 0) {
            reverse(line, len);
            printf("%s", line);
        }
    }

    return 0;
}

void reverse(char s[], int size)
{
    int i, j;

    for (i = 0, j = size - 2; i < j; ++i, --j) {
        char t = s[i];
        s[i]   = s[j];
        s[j]   = t;
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
