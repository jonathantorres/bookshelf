#include <stdio.h>

int main(int argc, char const *argv[])
{
    int line = 88;
    int length = 10;

    for (int i = 1; i <= length; i++) {
        if (i == 1 || i == length) {
            for (int j = 1; j <= length; j++) {
                printf("%c", line);
            }
        } else {
            for (int j = 1; j <= length; j++) {
                if (j == 1 || j == length) {
                    printf("%c", line);
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    return 0;
}
