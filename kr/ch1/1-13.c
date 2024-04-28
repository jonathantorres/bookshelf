#include <stdio.h>

#define WLEN 1024

int main(void)
{
    int c;
    int wl = 0;
    int j  = 0;
    int word_lengths[WLEN];

    for (int i = 0; i < WLEN; i++) {
        word_lengths[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            word_lengths[j++] = wl;
            wl                = 0;
        } else if (c == '.' || c == ',') {
            // ignore periods and commas
        } else {
            ++wl;
        }
    }

    // print histogram
    for (int i = 0; i < WLEN; i++) {
        if (word_lengths[i] > 0) {
            for (int j = 0; j < word_lengths[i]; j++) {
                putchar('-');
            }
            printf("\n");
        }
    }

    return 0;
}
