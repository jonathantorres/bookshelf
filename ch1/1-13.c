#include <stdio.h>

int main(void)
{
    int c;
    int index = 0;
    int word_lengths[50] = { 0 };
    int cur_length = 0;

    while((c = getchar()) != EOF) {
        if (c == ' ') {
            word_lengths[index] = cur_length;
            cur_length = 0;
            index++;
        } else {
            cur_length++;
        }

        if (c == '\n') {
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < word_lengths[i]; j++) {
                    printf("-");
                }
                printf("\n");
            }
        }
    }
    return 0;
}
