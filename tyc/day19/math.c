#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    double x;

    printf("Enter a number: ");
    scanf("%lf", &x);

    printf("\n\nOriginal value: %lf", x);
    printf("\nCeil: %lf", ceil(x));
    printf("\nFloor: %lf", floor(x));

    if (x >= 0) {
        printf("\nSquare root: %lf", sqrt(x));
    } else {
        printf("\nNegative number");
    }

    printf("\nCosine: %lf\n", cos(x));
    return 0;
}
