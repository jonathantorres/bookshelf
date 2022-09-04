#include <stdio.h>
#include <math.h>

#define MAXLINE 1000
#define LINELIMIT 10

int get_line(char s[], int lim);

int main(void)
{
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > LINELIMIT) {
            int split = (int)ceil((float)len/LINELIMIT);
            int char_s = 0;
            int char_e = LINELIMIT-1;
            for (int i = 1; i <= split; i++) {
                for (int j = char_s; j <= char_e; j++) {
                    putchar(line[j]);
                }
                if (i == split - 1) {
                    char_e += (len - char_e) - 1;
                } else {
                    char_e += LINELIMIT;
                }
                char_s += LINELIMIT;
                printf("\n");
            }
        } else {
            printf("%s", line);
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
