#include <ctype.h>
#include <stdio.h>

int htoi(char s[]);
int is_hexchar(char c);
int get_hex_val(char c);

int main(void)
{
    printf("%d\n", htoi("0xFF"));
    printf("%d\n", htoi("FF"));
    printf("%d\n", htoi("0xdead"));

    return 0;
}

int htoi(char s[])
{
    int n = 0;
    int i = 0;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }

    for (; is_hexchar(s[i]); ++i) {
        n = 16 * n + get_hex_val(s[i]);
    }

    return n;
}

int is_hexchar(char c)
{
    // numbers are valid hex
    if (c >= '0' && c <= '9') {
        return 1;
    }

    // letters from A to F are valid hex
    c = tolower(c);
    if (c >= 'a' && c <= 'f') {
        return 1;
    }

    return 0;
}

int get_hex_val(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    char chars[] = "abcdef";
    int i;
    c = tolower(c);

    for (i = 0; chars[i] != c; ++i) {
        //
    }

    return i + 10;
}
