#include <stdio.h>

int main(void)
{
    int c;
    int index = 0;
    int word_lens[50] = { 0 };
    int cur_len = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            word_lens[index] = cur_len;
            cur_len = 0;
            index++;
        } else {
            cur_len++;
        }

        if (c == '\n') {
            word_lens[index] = cur_len-1;
            cur_len = 0;
            index++;
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < word_lens[i]; j++) {
                    printf("-");
                }
                printf("\n");
            }
            index = 0;
        }
    }
    return 0;
}
