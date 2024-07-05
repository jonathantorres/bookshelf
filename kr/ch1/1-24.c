#include <stdio.h>

#define MAXLINE 1024

int line_is_comment(char line[], int maxline);
int getline(char line[], int maxline);

int main(void)
{
    int len;
    char line[MAXLINE];

    for (int i = 0; i < MAXLINE; ++i) {
        line[i] = 0;
    }

    int parens        = 0;
    int brackets      = 0;
    int braces        = 0;
    int double_quotes = 0;
    int single_quotes = 0;

    while ((len = getline(line, MAXLINE)) > 0) {
        // ignore comments
        if (line_is_comment(line, len)) {
            continue;
        }

        for (int i = 0; i < len; i++) {
            if (line[i] == '(' || line[i] == ')') {
                parens++;
            }

            if (line[i] == '[' || line[i] == ']') {
                brackets++;
            }

            if (line[i] == '{' || line[i] == '}') {
                braces++;
            }

            if (line[i] == '"') {
                double_quotes++;
            }

            if (line[i] == '\'') {
                single_quotes++;
            }
        }
    }

    if (parens % 2 != 0) {
        puts("Syntax error! Unbalanced parenthesis!");
        return 1;
    }

    if (brackets % 2 != 0) {
        puts("Syntax error! Unbalanced square brackets!");
        return 1;
    }

    if (braces % 2 != 0) {
        puts("Syntax error! Unbalanced braces!");
        return 1;
    }

    if (single_quotes % 2 != 0) {
        puts("Syntax error! Unbalanced single quotes!");
        return 1;
    }

    if (double_quotes % 2 != 0) {
        puts("Syntax error! Unbalanced double quotes!");
        return 1;
    }

    puts("Syntax ok");

    return 0;
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
