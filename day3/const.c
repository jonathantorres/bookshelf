#include <stdio.h>

#define GRAMS_PER_POUND 454

const int TARGET_YEAR = 2017;

long weight_in_grams, weight_in_pounds;
int year_of_birth, age_in_2017;

int main(int argc, char const *argv[])
{
    printf("Enter your weight in pounds: ");
    scanf("%ld", &weight_in_pounds);
    printf("Enter your year of birth: ");
    scanf("%d", &year_of_birth);

    weight_in_grams = weight_in_pounds * GRAMS_PER_POUND;
    age_in_2017 = TARGET_YEAR - year_of_birth;

    printf("\nYour weight in grams = %ld", weight_in_grams);
    printf("\nIn 2017 you will be %d years old\n", age_in_2017);

    return 0;
}
