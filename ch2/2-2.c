#include <stdio.h>

#define MAXLINE 1000

int main(void)
{
    int i = 0;
    int c;
    char s[MAXLINE];
    while ((c = getchar()) != EOF) {
        if (c != '\n') {
            if (i < MAXLINE) {
                s[i] = c;
                i++;
            }
        } else {
            s[i] = '\0';
            printf("%s\n", s);
            i = 0;
        }
    }
}
