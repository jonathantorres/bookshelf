#include <stdio.h>

#define MAXLINE 1024

void remove_comments(char line[], int maxline);
int line_is_comment(char line[], int maxline);
int line_is_ml_comment(char line[], int maxline);
int line_is_closing_ml_comment(char line[], int maxline);
int getline(char line[], int maxline);

int main(void)
{
    int len;
    int in_ml_comment = 0;
    char line[MAXLINE];

    for (int i = 0; i < MAXLINE; ++i) {
        line[i] = 0;
    }

    while ((len = getline(line, MAXLINE)) > 0) {
        if (line_is_ml_comment(line, len)) {
            in_ml_comment = 1;
            continue;
        }

        if (line_is_closing_ml_comment(line, len)) {
            in_ml_comment = 0;
            continue;
        }

        if (in_ml_comment == 0 && !line_is_comment(line, len)) {
            remove_comments(line, len);
            printf("%s", line);
        }
    }

    return 0;
}

void remove_comments(char line[], int maxline)
{
    for (int i = 0; i < maxline; ++i) {
        char c = line[i];

        // once we see a comment, ignore the rest of the line
        if (c == '/' && (line[i + 1] == '/' || line[i + 1] == '*')) {
            line[i++] = '\n';
            line[i]   = '\0';
            break;
        }
    }
}

int line_is_comment(char line[], int maxline)
{
    int is_comment = 0;
    int has_char   = 0;

    for (int i = 0; i < maxline; ++i) {
        char c = line[i];

        if (c != ' ' && c != '\n' && c != '\t' && c != '/' && c != '*') {
            has_char = 1;
        }

        if (c == '/' && (line[i + 1] == '/' || line[i + 1] == '*') && has_char == 0) {
            is_comment = 1;
            break;
        }
    }

    return is_comment;
}

int line_is_ml_comment(char line[], int maxline)
{
    int open_found    = 0;
    int closing_found = 0;

    // if we don't see the closing multiline comment, then this is a multiline comment
    for (int i = 0; i < maxline; ++i) {
        char c = line[i];

        if (c == '/' && line[i + 1] == '*') {
            open_found = 1;
        }

        if (c == '*' && line[i + 1] == '/') {
            closing_found = 1;
            break;
        }
    }

    if (open_found == 1 && closing_found == 0) {
        return 1;
    }

    return 0;
}

int line_is_closing_ml_comment(char line[], int maxline)
{
    int found = 0;

    for (int i = 0; i < maxline; ++i) {
        char c = line[i];

        if (c == '*' && line[i + 1] == '/') {
            found = 1;
            break;
        }
    }

    return found;
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
