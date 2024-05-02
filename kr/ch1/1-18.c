#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int line_is_blank(char line[], int size);
void trimline(char line[], char tline[], int size);

int main(void)
{
    int len;
    char line[MAXLINE];
    char tline[MAXLINE];

    for (int i = 0; i < MAXLINE; i++) {
        line[i]  = 0;
        tline[i] = 0;
    }

    while ((len = getline(line, MAXLINE)) > 0) {
        // ignore blank lines
        if (line_is_blank(line, len)) {
            continue;
        }

        trimline(line, tline, len);

        printf("%s", tline);
    }

    return 0;
}

void trimline(char line[], char tline[], int size)
{
    // trim the beginning of the line
    int found, i, j;
    found = i = j = 0;

    while (line[i] != '\0') {
        if (line[i] != ' ' && line[i] != '\t') {
            found = 1;
        }

        if (found) {
            tline[j++] = line[i];
        } else {
            size--;
        }
        ++i;
    }

    // trim the end of the line
    j = found = 0;
    for (i = size - 2; i >= 0; --i) {
        if (tline[i] != ' ' && tline[i] != '\t') {
            found = 1;
        }

        if (found) {
            j = i;
            break;
        }
    }

    tline[++j] = '\n';
    tline[++j] = '\0';
}

int line_is_blank(char line[], int size)
{
    int blank = 1;

    for (int i = 0; i < size - 1; ++i) {
        int c = line[i];
        if (c != ' ' && c != '\t' && c != '\n') {
            blank = 0;
            break;
        }
    }

    return blank;
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
