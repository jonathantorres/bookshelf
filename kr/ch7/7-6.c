#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{
    FILE *f1, *f2;
    char line1[MAXLINE], line2[MAXLINE];
    char *prog = argv[0];

    if (argc != 3) {
        printf("error: the program takes 2 arguments\n");
        return 0;
    }

    if ((f1 = fopen(*++argv, "r")) != NULL) {
        if ((f2 = fopen(*++argv, "r")) != NULL) {
            while (fgets(line1, MAXLINE, f1) != NULL && fgets(line2, MAXLINE, f2) != NULL) {
                if (strcmp(line1, line2) != 0) {
                    printf("%s", line1);
                    printf("%s", line2);

                    fclose(f1);
                    fclose(f2);

                    return 0;
                }
            }
        } else {
            fprintf(stderr, "%s can't open %s", prog, *argv);
            exit(1);
        }
    } else {
        fprintf(stderr, "%s can't open %s", prog, *argv);
        exit(1);
    }

    printf("Identical lines\n");

    return 0;
}
