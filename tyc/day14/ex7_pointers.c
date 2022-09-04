#include <stdio.h>

typedef struct {
    char letter;
    int count;
} letter_summary;

#define ARRAY_LENGTH 100

int letter_is_in_summary(int letter, letter_summary **p_letters);
void add_letter_to_summary(int letter, letter_summary **p_letters);

int main(void)
{
    int ch;
    letter_summary *p_letters;
    letter_summary letters[ARRAY_LENGTH];
    p_letters = letters;

    // initialize array
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        p_letters->letter = 0;
        p_letters->count = 0;
        p_letters++;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        // reset pointer after assigning values
        p_letters = letters;

        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
            if (letter_is_in_summary(ch, &p_letters) == 1) {
                p_letters->count++;
                p_letters = letters;
            } else {
                p_letters = letters;
                add_letter_to_summary(ch, &p_letters);
            }
        }
    }

    // print summary
    puts("Summary of Results!");
    puts("");
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        if (p_letters->letter != 0) {
            printf("Letter: %c - Amount: %d\n", p_letters->letter, p_letters->count);
        }
        p_letters++;
    }

    return 0;
}

void add_letter_to_summary(int letter, letter_summary **p_letters)
{
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        if ((*p_letters)->letter == 0) {
            (*p_letters)->letter = (char) letter;
            (*p_letters)->count++;
            break;
        }
        (*p_letters)++;
    }
}

int letter_is_in_summary(int letter, letter_summary **p_letters)
{
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        if ((*p_letters)->letter != 0 && (*p_letters)->letter == (char) letter) {
            return 1;
        }

        (*p_letters)++;
    }

    return 0;
}
