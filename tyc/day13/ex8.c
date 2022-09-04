#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long num1;
    long num2;
    char operator;
} calculation;

calculation get_values(void);
void display_result(long result);
void exit_calculator(int status_code);

int main(int argc, char const *argv[])
{
    long result = 0;

    puts("Opening calculator... press Ctrl+C to exit.");

    while (1) {
        calculation calc = get_values();

        switch (calc.operator) {
            default:
                puts("Operation not recognized.");
                exit_calculator(EXIT_FAILURE);
                break;
            case '+':
                result = calc.num1 + calc.num2;
                display_result(result);
                break;
            case '-':
                result = calc.num1 - calc.num2;
                display_result(result);
                break;
            case '/':
                result = calc.num1 / calc.num2;
                display_result(result);
                break;
            case '*':
                result = calc.num1 * calc.num2;
                display_result(result);
                break;
        }
    }

    return 0;
}

void display_result(long result)
{
    printf("= %ld\n", result);
}

void exit_calculator(int status_code)
{
    puts("Exiting...");
    exit(status_code);
}

calculation get_values(void)
{
    long num1;
    long num2;
    char operator;
    calculation calc;

    int input_result = scanf("%ld %c %ld", &num1, &operator, &num2);

    if (input_result == EOF) {
        exit_calculator(EXIT_FAILURE);
    }

    calc.num1 = num1;
    calc.num2 = num2;
    calc.operator = operator;

    return calc;
}
