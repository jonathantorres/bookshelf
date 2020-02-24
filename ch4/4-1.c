#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t);

int main(void)
{
    char msg[] = "Hola Jonathan";
    printf("%d\n", strrindex(msg, 'a'));
    return 0;
}

int strrindex(char s[], char t)
{
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (s[i] == t) {
            return i;
        }
    }
    return -1;
}
