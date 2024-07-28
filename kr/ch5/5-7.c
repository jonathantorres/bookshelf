#include <stdio.h>
#include <string.h>

#define MAXLEN  1024
#define MAXSTOR 5120

int getline(char *s, int lim);
int readlines(char *lineptr[], char *linestor, int maxlines);
void writelines(char *lineptr[], int nlines);

char *lineptr[MAXSTOR];

int main(void)
{
    char linestor[MAXSTOR];
    int nlines;

    while ((nlines = readlines(lineptr, linestor, MAXLEN)) >= 0) {
        writelines(lineptr, nlines);
    }

    return 0;
}

int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p        = linestor;
    char *linestop = linestor + MAXSTOR;
    nlines         = 0;

    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > linestop) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
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
