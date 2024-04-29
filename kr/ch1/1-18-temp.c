#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int line_is_blank(char line[], int size);
void trimline(char line[], char trimmed[], int size);

int main(void)
{
    int len;
    char line[MAXLINE];
    char trimmed[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        // ignore blank lines
        if (line_is_blank(line, len)) {
            continue;
        }

        trimline(line, trimmed, len);

        printf("%s", trimmed);
    }

    return 0;
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

void trimline(char line[], char trimmed[], int size)
{
    // trim the beginning of the line
    int i, j;
    int char_found = 0;
    i = j = 0;

    while (line[i] != '\0') {
        if (line[i] != ' ' && line[i] != '\t') {
            char_found = 1;
        }

        if (char_found) {
            trimmed[j++] = line[i];
        }
        ++i;
    }
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
