#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (line[0] == '\t' || line[0] == ' ') {
            for (int i = 0; i < len; i++) {
                line[i] = line[i+1];
            }
        }

        if (line[len-2] == '\t' || line[len-2] == ' ') {
            line[len-2] = 0;
        }

        int all_blanks = 1;
        for (int j = 0; j < len; j++) {
            if (line[j] != ' ' && line[j] != '\t' && line[j] != '\n' && line[j] != '\0') {
                all_blanks = 0;
            }
        }
        if (all_blanks) {
            continue;
        }
        printf("%s", line);
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
