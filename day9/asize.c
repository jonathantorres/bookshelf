#include <stdio.h>

int ctr;
short array_s[10];
float array_f[10];
double array_d[10];

int main(int argc, char const *argv[])
{
    printf("\t\tShort\t\t\tFloat\t\t\tDouble");
    printf("\n==========================================");
    printf("=====================================");

    for (ctr = 0; ctr < 10; ctr++) {
        printf("\nElement %d: \t%ld\t\t%ld\t\t%ld", (ctr + 1), &array_s[ctr], &array_f[ctr], &array_d[ctr]);
    }

    printf("\n==========================================");
    printf("=====================================\n");

    return 0;
}
