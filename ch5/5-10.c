#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char **op;
    int pos = 0;
    float result;

    if (argc < 4) {
        printf ("not enough arguments: expr numbers operators\n");
        exit(1);
    }
    while (isdigit((*++argv)[0])) {
        pos++;
    }
    op = argv-1;
    result = atof(*--argv);
    while (--pos > 0 && (++op != NULL) && (--argv != NULL)) {
        switch((*op)[0]) {
            case '+':
                result += atof(*argv);
                break;
            case '-':
                result = atof(*argv) - result;
                break;
            case '*':
                result *= atof(*argv);
                break;
            case '/':
                result = atof(*argv) / result;
                break;
            default:
                printf("invalid operator!\n");
                pos = 0;
                break;
        }
    }
    printf("The result is: %.2f\n", result);
    return 0;
}
