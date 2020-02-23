#include <stdio.h>

void expand(char s1[], char s2[]);

int main(void)
{
    char s1[] = "a-zA-Z0-9";
    char s2[1000];

    expand(s1, s2);
    printf("%s\n", s2);
    return 0;
}

void expand(char s1[], char s2[])
{
    int k = 0;
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] == '-') {
            for (int j = s1[i-1]; j <= s1[i+1]; j++, k++) {
                s2[k] = (char)j;
            }
        }
    }
    s2[k+1] = '\0';
}
