#include <stdio.h>
#include <string.h>

#define MAXLEN 1000   // max length of any input line
#define MAXSTOR 5000  // max length of storage

int c_getline(char *s, int lim);
int readlines(char *lineptr[], char *linestor, int maxlines);

int main(void)
{
    char line[MAXLEN];
    while (c_getline(line, MAXLEN) > 0) {
        printf("%s\n", line);
    }
    return 0;
}

int c_getline(char *s, int lim)
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

int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;
    char *linestop = linestor + MAXSTOR;
    nlines = 0;
    while ((len = c_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > linestop) {
          return -1;
        } else {
            line[len-1] = '\0';   // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}
