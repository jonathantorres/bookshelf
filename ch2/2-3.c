#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int get_map(char c);
int htoi(char s[]);

int main(void)
{
    // always assume it's a valid hex value
    char s1[] = "0xFF00FF";
    char s2[] = "cc0033";

    printf("%d\n", htoi(s1));
    printf("%d\n", htoi(s2));
    return 0;
}

int get_map(char c)
{
    char map[] = "0123456789abcdef";
    int pos = 0;
    for (int i = 0; i < (int)strlen(map); i++) {
        if (tolower(c) == map[i]) {
            pos = i;
            break;
        }
    }
    return pos;
}

int htoi(char s[])
{
    int total = 0;
    int with_prefix = 0;
    int i = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
        with_prefix = 1;
    }
    for (int j = strlen(s)-1; s[i] != '\0'; i++,j--) {
        total += get_map(s[i]) * pow(16, j - (with_prefix == 1 ? 2 : 0));
    }
    return total;
}
