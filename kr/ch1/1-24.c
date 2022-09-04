#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim);

int main(void)
{
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        int parens_l = 0;
        int brackets_l = 0;
        int double_q_l = 0;
        int single_q_l = 0;
        int comm_err = 0;
        for (int i = 0; i < len; i++) {
            if (line[i] == '(' || line[i] == ')') {
                parens_l++;
            }
            if (line[i] == '[' || line[i] == ']') {
                brackets_l++;
            }
            if (line[i] == '"') {
                double_q_l++;
            }
            if (line[i] == '\'') {
                single_q_l++;
            }
            if (line[i] == '/' && line[i+1] == '/') {
                break;
            } else if (line[i] == '/') {
                comm_err = 1;
            }
        }
        if (parens_l%2 != 0 || brackets_l%2 != 0 || single_q_l%2 != 0 || double_q_l%2 != 0 || comm_err != 0) {
            puts("Syntax error!");
        }
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
