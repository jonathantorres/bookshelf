#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUMBERS 3

void sort_numbers(double *numbers[MAX_NUMBERS], int sort_type);
void print_numbers(double *numbers[MAX_NUMBERS]);
bool sort_asc(double v1, double v2);
bool sort_desc(double v1, double v2);

int main(void)
{
    double *numbers[MAX_NUMBERS];
    double *current_number;
    int entered_numbers = 0;
    int sort_type;

    while (1) {
        if (entered_numbers == MAX_NUMBERS) {
            break;
        }

        current_number = (double*) malloc(sizeof(double));

        if (current_number == NULL) {
            puts("Memory allocation error.");
            exit(EXIT_FAILURE);
        }

        puts("Please enter a number: ");
        scanf("%lf", current_number);

        numbers[entered_numbers] = current_number;
        entered_numbers++;
    }

    puts("Enter the sort type: 0 for ASC, 1 for DESC");
    scanf("%d", &sort_type);

    if (sort_type != 0 && sort_type != 1) {
        sort_type = 0;
    }

    sort_numbers(numbers, sort_type);
    print_numbers(numbers);

    return 0;
}

void sort_numbers(double *numbers[MAX_NUMBERS], int sort_type)
{
    double *tmp;
    bool (*sort_func)(double v1, double v2);

    if (sort_type == 0) {
        sort_func = sort_asc;
    } else {
        sort_func = sort_desc;
    }

    for (int i = 1; i < MAX_NUMBERS; i++) {
        for (int j = 0; j < MAX_NUMBERS - 1; j++) {
            if (sort_func(*numbers[j], *numbers[j + 1])) {
                tmp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = tmp;
            }
        }
    }
}

void print_numbers(double *numbers[MAX_NUMBERS])
{
    puts("Entered all numbers, numbers are...");

    for (int i = 0; i < MAX_NUMBERS; i++) {
        printf("%f\n", *numbers[i]);
    }
}

bool sort_asc(double v1, double v2)
{
    return v1 > v2;
}

bool sort_desc(double v1, double v2)
{
    return v1 < v2;
}
