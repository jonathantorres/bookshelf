#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim);
void r_escape(char s[], char t[]);
void escape(char s[], char t[]);

int main(void)
{
    char line[MAXLINE];
    char line2[MAXLINE];
    char line3[MAXLINE];
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        escape(line2, line);
        r_escape(line3, line2);
        printf("%s\n", line2);
        printf("%s\n", line3);
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

void r_escape(char s[], char t[])
{
    int i, j;
    for (i = 0, j = 0; t[i] != '\0'; i++, j++) {
        switch (t[i]) {
            case '\\':
                if (t[i+1] == 't') {
                    s[j] = '\t';
                    i++;
                } else if (t[i+1] == 'n') {
                    s[j] = '\n';
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

void escape(char s[], char t[])
{
    int i, j;
    for (i = 0, j = 0; t[i] != '\0'; i++, j++) {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j] = 't';
                break;
            default:
                s[j] = t[i];
                break;
        }
    }
    s[j] = '\0';
}
