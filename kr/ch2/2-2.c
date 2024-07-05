#include <stdio.h>

#define MAXLINE 1024

int main(void)
{
    char line[MAXLINE];
    int i = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c != '\n') {
            if (i < MAXLINE) {
                line[i++] = c;
            }
        } else {
            line[i] = '\0';
            printf("%s\n", line);
        }
    }

    return 0;
}
