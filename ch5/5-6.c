#include <stdio.h>
#include <string.h>

int get_line(char *s, int lim);
void reverse(char *s);

int main(void)
{
    int lim = 100;
    char msg[lim];
    get_line(msg, lim);
    printf("%s", msg);
    return 0;
}

void reverse(char *s)
{
    char *t;
    int c;
    for (t = s + (strlen(s)-1); s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}

int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return i;
}
