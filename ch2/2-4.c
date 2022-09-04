#include <stdio.h>

void squeeze(char s1[], const char s2[]);

int main(void)
{
    char name[] = "Jonathan";
    printf("%s\n", name);
    squeeze(name, "Ja");
    printf("%s\n", name);
    return 0;
}

void squeeze(char s1[], const char s2[])
{
    int i, j, k;
    for (i = 0, k = 0; s1[i] != '\0'; i++) {
        int in_s2 = 0;
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                in_s2 = 1;
                break;
            }
        }
        if (in_s2 == 0) {
            s1[k++] = s1[i];
        }
    }
    s1[k] = '\0';
}
