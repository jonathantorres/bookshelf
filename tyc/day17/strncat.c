#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[27];
    char *str2 = "abcdefghijklmnopqrstuvwxyz";
    int n;

    for (n = 1; n < 27; n++) {
        strcpy(str1, "");
        strncat(str1, str2, n);
        puts(str1);
    }

    return 0;
}
