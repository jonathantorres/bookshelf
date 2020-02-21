#include <stdio.h>

#define MAX 50

int main(void)
{
    int c;
    int len = 0;
    char chars[MAX] = { 0 };
    int freqs[MAX] = { 0 };

    while((c = getchar()) != EOF) {
        if (c == ' ') {
            continue;
        }

        if (c == '\n') {
            break;
        }

        int in_chars = 0;
        for (int i = 0; i < len; i++) {
            if (chars[i] == c) {
                in_chars = 1;
                freqs[i]++;
                break;
            }
        }

        if (in_chars == 0) {
            chars[len] = c;
            freqs[len] = 1;
            len++;
        }
    }

    for (int i = 0; i < len; i++) {
        printf("%c ", chars[i]);
        for (int j = 0; j < freqs[i]; j++) {
            printf("-");
        }
        printf("\n");
    }
    return 0;
}
