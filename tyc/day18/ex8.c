#include <stdio.h>
#include <string.h>

char *char_in_string(char ch, char *str);

int main(void)
{
    char ch = 'h';
    char str[] = "Jonathan";
    char *ch_p;

    ch_p = char_in_string(ch, str);

    printf("Found character %c at index %ld\n", *ch_p, ch_p - str);
    return 0;
}

char *char_in_string(char ch, char *str)
{
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        if ((int)ch == (int)*str) {
            return str;
        }
        str++;
    }

    return NULL;
}
