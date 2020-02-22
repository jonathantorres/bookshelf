#include <stdio.h>

int any(char s1[], char s2[]);

int main(void)
{
    char s1[] = "Jonathan";
    char s2[] = "ona";
    char s3[] = "bum";

    printf("%d\n", any(s1, s2)); // 1
    printf("%d\n", any(s1, s3)); // -1
    return 0;
}

int any(char s1[], char s2[])
{
    int i, j;
    int index = -1;
    for (i = 0; s1[i] != '\0'; i++) {
        int found = 0;
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                index = i;
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return index;
}
