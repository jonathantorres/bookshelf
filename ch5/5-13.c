#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define PLINES 10

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int process_input(char *v[]);

int main(int argc, char *argv[])
{
    int nlines;

    switch (argc) {
        case 1:
            nlines = PLINES;
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

    if ((readlines(lineptr, MAXLINES)) >= 0) {
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
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

#define MAXLEN 1000
int get_line(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 50000           // size of available space
static char allocbuf[ALLOCSIZE];  // storage for alloc
static char *allocp = allocbuf;   // next free position

char *alloc(int n)
{
    // if it fits
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i, n = 1;
    printf("\n");
    while (*++lineptr != NULL) {
        n++;
    }
    for (i = 0; i < (nlines+1) && i < (n+1); i++) {
        *--lineptr;
    }
    while (*++lineptr != NULL) {
        printf("%s\n", *lineptr);
    }
}
