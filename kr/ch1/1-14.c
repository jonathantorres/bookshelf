#include <stdio.h>

#define LEN 256

int main(void)
{
    int c;
    int chars[LEN];

    for (int i = 0; i < LEN; i++) {
        chars[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n' && c != '.' && c != ',') {
            chars[c]++;
        }
    }

    // print histogram
    for (int i = 0; i < LEN; i++) {
        if (chars[i] > 0) {
            printf("%c ", i);

            for (int j = 0; j < chars[i]; j++) {
                putchar('-');
            }

            putchar('\n');
        }
    }

    return 0;
}
