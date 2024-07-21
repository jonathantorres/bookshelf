#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int getline(char s[], int lim);

#define MAXLINE 1024

int main(void)
{
    int len;
    char a[MAXLINE];
    char b[MAXLINE];
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        escape(a, line);
        unescape(b, line);

        printf("%s\n", a);
        printf("%s\n", b);
    }

    return 0;
}

void escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; ++i) {
        char c = t[i];

        switch (c) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\r':
                s[j++] = '\\';
                s[j++] = 'r';
                break;
            default:
                s[j++] = c;
                break;
        }
    }

    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; i++, j++) {
        switch (t[i]) {
            case '\\':
                if (t[i + 1] == 't') {
                    s[j] = '\t';
                    i++;
                } else if (t[i + 1] == 'n') {
                    s[j] = '\n';
                    i++;
                } else if (t[i + 1] == 'r') {
                    s[j] = '\r';
                    i++;
                } else {
                    s[j] = t[i];
                }
                break;
            default:
                s[j] = t[i];
                break;
        }
    }

    s[j] = '\0';
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
