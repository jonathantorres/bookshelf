#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_r(char s[]);

int main(void)
{
    char s[] = "Jonathan Torres";
    printf("%s\n", s);
    reverse_r(s);
    printf("%s\n", s);
    return 0;
}

// reverse: reverse string s in place
void reverse_r(char s[])
{
    static int i = 0;
    static int k = 1;
    int j = strlen(s) - k;
    int c;
    if (i < j) {
        c = s[i];
        s[i++] = s[j];
        s[j] = c;
        k++;
        reverse_r(s);
    }
}
