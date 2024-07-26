#include <stdio.h>
#include <string.h>

void reverse(char s[]);

#define MAXLINE 1024

int main(void)
{
    char a[] = "Jonathan Torres";
    char b[] = "This is a test message";
    char c[] = "Try to reverse this: 123846";

    reverse(a);
    reverse(b);
    reverse(c);

    printf("%s\n", a);
    printf("%s\n", b);
    printf("%s\n", c);

    return 0;
}

void reverse(char s[])
{
    static int i = 0;
    static int j = 0;
    int c;

    if (i == 0) {
        j = strlen(s) - 1;
    }

    if (i >= j) {
        i = 0;
        j = 0;
        return;
    }

    c      = s[i];
    s[i++] = s[j];
    s[j--] = c;

    reverse(s);
}
