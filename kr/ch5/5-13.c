#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTOR    5120
#define PRINTLINES 10
#define ALLOCSIZE  50000
#define MAXLEN     1024

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int getline(char *s, int lim);
char *alloc(int n);
int process_input(char *v[]);

char *lineptr[MAXSTOR];

int main(int argc, char *argv[])
{
    int nlines;

    switch (argc) {
        case 1:
            nlines = PRINTLINES;
            break;
        case 2:
            nlines = process_input(argv);
            if (nlines == -1) {
                printf("Invalid format for optional argument -n\n");
                return 0;
            }
            break;
        default:
            printf("Too many arguments!\n");
            return 0;
    }

    if ((readlines(lineptr, MAXSTOR)) >= 0) {
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int process_input(char *v[])
{
    char *n, c;
    n = v[1];

    if (n[0] != '-') {
        return -1;
    } else {
        while (!(isdigit(c = *++n)) && c != '\0') {
            ;
        }
        if (c == '\0') {
            return -1;
        } else {
            return (atoi(n));
        }
    }
}

void writelines(char *lineptr[], int nlines)
{
    int i, n = 1;

    printf("\n");

    while (*++lineptr != NULL) {
        n++;
    }

    for (i = 0; i < (nlines + 1) && i < (n + 1); i++) {
        --lineptr;
    }

    while (*++lineptr != NULL) {
        printf("%s\n", *lineptr);
    }
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

int getline(char *s, int lim)
{
    int c;
    int i = 0;

    while (--lim > 0 && ((c = getchar()) != EOF && c != '\n')) {
        i++;
        *s++ = c;
    }

    if (c == '\n') {
        i++;
        *s++ = '\n';
    }

    *s = '\0';

    return i;
}
