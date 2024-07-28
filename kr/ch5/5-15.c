#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTOR   5120
#define MAXLEN    1024
#define ALLOCSIZE 50000

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *), int r, int f);
int getline(char *s, int lim);
char *alloc(int n);
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);
void lower(char v[]);

char *lineptr[MAXLEN];

int main(int argc, char *argv[])
{
    int nlines, i = 0, j = 1;
    int numeric  = 0;
    int reversed = 0;
    int fold;

    if (argc > 1) {
        while (++i < argc) {
            while (argv[i][j] != '\0') {
                switch (argv[i][j++]) {
                    case 'n':
                        numeric = 1;
                        break;
                    case 'r':
                        reversed = 1;
                        break;
                    case 'f':
                        fold = 1;
                        break;
                }
            }

            j = 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLEN)) >= 0) {
        qsort2((void **)lineptr, 0, nlines - 1,
               numeric ? (int (*)(void *, void *))numcmp : (int (*)(void *, void *))strcmp,
               reversed ? 1 : 0, fold ? 1 : 0);
        writelines(lineptr, nlines);
        return 0;
    }

    printf("input too big to sort\n");

    return 1;
}

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *), int reversed, int fold)
{
    int i, last;
    char v1[1000], v2[1000];

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if (fold) {
            strcpy(v1, v[i]);
            strcpy(v2, v[left]);
            lower(v1);
            lower(v2);
        } else {
            strcpy(v1, v[i]);
            strcpy(v2, v[left]);
        }

        if (!reversed) {
            if ((*comp)(v1, v2) < 0) {
                swap(v, ++last, i);
            } else {
                if ((*comp)(v1, v2) > 0) {
                    swap(v, ++last, i);
                }
            }
        }
    }

    swap(v, left, last);
    qsort2(v, left, last - 1, comp, reversed, fold);
    qsort2(v, last + 1, right, comp, reversed, fold);
}

void lower(char v[])
{
    int i = 0;

    while (v[i]) {
        v[i] = tolower(v[i]);
        i++;
    }
}

int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
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
