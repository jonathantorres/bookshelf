#include <stdio.h>

void squeeze(char s[], char t[]);

int main(void)
{
    char s[] = "Jonathan Torres";
    char t[] = "an";

    printf("%s\n", s);
    squeeze(s, t);
    printf("%s\n", s); // Joth Torres

    return 0;
}

void squeeze(char s[], char t[])
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; ++i) {
        int found = 0;

        for (int k = 0; t[k] != '\0'; ++k) {
            if (t[k] == s[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            s[j++] = s[i];
        }
    }

    s[j] = '\0';
}
