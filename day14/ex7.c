#include <stdio.h>

typedef struct {
    char letter;
    int count;
} letter_summary;

int main(void)
{
    int ch;
    letter_summary letters[100];

    // initialize array
    for (int i = 0; i < 100; i++) {
        letters[i].letter = 0;
        letters[i].count = 0;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
            int letter_in_summary = 0;
            int letter_index = 0;
            for (int i = 0; i < 100; i++) {
                if (letters[i].letter != 0 && letters[i].letter == (char) ch) {
                    letter_in_summary = 1;
                    letter_index = i;
                    break;
                }
            }

            if (letter_in_summary == 1) {
                letters[letter_index].count++;
            } else {
                for (int j = 0; j < 100; j++) {
                    if (letters[j].letter == 0) {
                        letters[j].letter = (char) ch;
                        letters[j].count++;
                        break;
                    }
                }
            }
        }
    }

    // print summary
    puts("Summary of Results!");
    puts("");
    for (int i = 0; i < 100; i++) {
        if (letters[i].letter != 0) {
            printf("Letter: %c - Amount: %d\n", letters[i].letter, letters[i].count);
        }
    }

    return 0;
}
