#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define PATTERNLEN 100

int get_line(char *line, int max);

int main(int argc, char *argv[])
{
    FILE *f;
    char line[MAXLINE], *pattern;
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    int argn = 1;
    while (++argn < argc && ((*++argv)[0] == '-')) {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }

    if (argn++ <= argc) {
        pattern = *argv;
        if (argn <= argc) {
            lineno = 0;
            while (*++argv != NULL) {
                printf("%s\n", *argv);
                if ((f = fopen(*argv, "r")) != NULL) {
                    while (fgets(line, MAXLINE, f) != NULL) {
                        lineno++;
                        if ((strstr(line, pattern) != NULL) != except) {
                            if (number) {
                                printf("%ld:", lineno);
                            }
                            printf("%s", line);
                            found++;
                        }
                    }
                } else {
                    printf("error: could not open %s", * argv);
                }
            }
        } else {
            while (get_line(line, MAXLINE) > 0) {
                lineno++;
                if ((strstr(line, pattern) != NULL) != except) {
                    if (number) {
                        printf("%ld:", lineno);
                    }
                    printf("%s", line);
                    found++;
                }
            }
        }
    } else {
        printf("Usage: find -x -n pattern [textfile\\s]\n");
    }
    return found;
}

int get_line(char * s, int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}
