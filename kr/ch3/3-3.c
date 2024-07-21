#include <stdio.h>

#define MAXLINE 1024

void expand(char s1[], char s2[]);

int main(void)
{
    char s1[MAXLINE];
    char s2[MAXLINE];
    char s3[MAXLINE];

    expand("a-z", s1);
    expand("a-b-c-", s2);
    expand("-a-z0-9", s3);

    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);

    return 0;
}

void expand(char s1[], char s2[])
{
    int i = 0;
    int j = 0;

    // initial dash
    if (s1[i] == '-') {
        s2[j++] = s1[i++];
    }

    char start, end;

    for (; s1[i] != '\0'; i++) {
        char c = s1[i];

        if (c == '-' && s1[i + 1] != '\0') {
            start = s1[i - 1];
            end   = s1[i + 1];

            if (start == s2[j - 1]) {
                start++;
            }

            // build the string
            while (start <= end) {
                s2[j++] = start++;
            }
        }
    }

    // trailing dash
    if (s1[i - 1] == '-') {
        s2[j++] = s1[i - 1];
    }

    s2[j] = '\0';
}
