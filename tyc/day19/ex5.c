#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    while (1) {
        int selected_math_function;
        double value = 0;
        double function_value;
        double (*ptr_math_function)(double val);

        puts("Choose a Math function");
        puts("1: acos()");
        puts("2: asin()");
        puts("Use any other value to exit.");

        if (
            fscanf(stdin, "%d", &selected_math_function) == 0
            || feof(stdin)
            || selected_math_function > 2
        ) {
            break;
        }

        printf("Enter the value: ");
        fscanf(stdin, "%lf", &value);
        puts("");

        switch (selected_math_function) {
            case 1: {
                ptr_math_function = acos;
                printf("Using the acos() function...value is: ");
                break;
            }
            case 2: {
                ptr_math_function = asin;
                printf("Using the asin() function...value is: ");
                break;
            }
            default: {
                puts("The selected function is not supported. Please choose another one");
            }
        }

        function_value = ptr_math_function(value);
        printf("%f\n", function_value);
    }

    return 0;
}
