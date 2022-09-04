#include <stdio.h>

#define MAXLINE 1000
#define TABLEN 4

int get_line(char s[], int lim);
void entab(char s[], int len, char ts);
void detab(char s[], int len, char ts);

int main(int argc, char **argv)
{
    char line[MAXLINE];
    int len;
    char ts = '\t';

    if (argc > 1) {
        ts = argv[1][0];
    }

    while ((len = get_line(line, MAXLINE)) > 0) {
        entab(line, len, ts);
        detab(line, len, ts);
        printf("%s\n", line);
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

void entab(char s[], int len, char ts)
{
    for (int i = 0; i < len; i++) {
        if (i >= 3 && s[i] == ' ' && s[i-1] == ' ' && s[i-2] == ' ' && s[i-3] == ' ') {
            putchar(ts);
        } else {
            putchar(s[i]);
        }
    }
}

void detab(char s[], int len, char ts)
{
    int found_times = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == ts) {
            found_times++;
            s[i] = ' ';
            for (int j = len-1; j >= i+1; j--) {
                s[j+(TABLEN-1)] = s[j];
            }
            for (int k = 1; k < TABLEN; k++) {
                s[i+k] = ' ';
            }
        }
    }
    len += (TABLEN*found_times);
    s[len] = '\0';
}
