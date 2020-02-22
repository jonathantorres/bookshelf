#include <stdio.h>

#define MAXLINE 1000
#define TABLEN 4

int get_line(char s[], int lim);
void detab(char s[], int len);

int main(void)
{
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        detab(line, len);
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

void detab(char s[], int len)
{
    int found_times = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '\t') {
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
