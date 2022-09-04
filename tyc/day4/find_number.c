#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NO 0
#define YES 1

int main(int argc, char const *argv[])
{
    int guess_value = -1;
    int number;
    int number_of_guesses = 0;
    int done = NO;

    printf("\n\nGetting a random number...\n");

    srand((unsigned) time(NULL));
    number = rand();

    while (done == NO) {
        printf("\nPick a number between 0 and %d ", RAND_MAX);
        scanf("%d", &guess_value);

        number_of_guesses++;

        if (number == guess_value) {
            done = YES;
        } else if (number < guess_value) {
            printf("\nYou guessed high!");
        } else {
            printf("\nYou guessed low!");
        }
    }

    printf("\n\nCongratulations! You guessed right in %d guesses!", number_of_guesses);
    printf("\n\nThe number was %d\n\n", number);

    return 0;
}
