#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 10000   // max number of lines
#define MAXLEN 1000      // max length of line array
#define ALLOCSIZE 50000  // size of available space

int get_line(char* s, int lim);
char *alloc(int n);
int readlines(char* lineptr[], int maxlines);
void writelines(char* lineptr[], int nlines);
void quicksort(void *v[], int left, int right, int (*)(void*, void*));
void swap(void *v[], int i, int j);
int numcmp(char*, char*);
int mystrcmp(char*, char*);

static char allocbuf[ALLOCSIZE];  // storage for alloc
static char *allocp = allocbuf;   // next free position

char *lineptr[MAXLINES];  /* pointers to text lines */
int decreasing = 0;       /* 0 if increasing, 1 if decreasing   -r flag */
int numeric = 0;          /* 1 if numeric sort   -n flag */
int fold = 0;             /* 1 if not case-sensitive   -f flag */
int directory = 0;        /* 1 if directory sort   -d flag */

int main(int argc, char *argv[])
{
    int nlines, i;

    while (--argc > 0) {
        ++argv;
        if ((*argv)[0] == '-') {
            for(i = 1; (*argv)[i]; ++i) {
                switch ((*argv)[i]) {
                    case 'n':
                        numeric = 1;
                    break;
                    case 'f':
                        fold = 1;
                    break;
                    case 'r':
                        decreasing = 1;
                    break;
                    case 'd':
                        directory = 1;
                    break;
                    default:
                        printf("usage: sort -dfnr\n");
                    return 1;
                }
            }
        } else {
            printf("usage: sort -dfnr\n");
            return 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric) {
            quicksort(
                (void**) lineptr,
                0,
                nlines - 1,
                (int (*)(void*, void*))numcmp
            );
        } else {
            quicksort(
                (void**) lineptr,
                0,
                nlines - 1,
                (int (*)(void*, void*))mystrcmp
            );
            writelines(lineptr, nlines);
            return 0;
        }
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void quicksort(void *v[], int left, int right, int (*comp)(void*, void*))
{
    int i, last;

    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);  /* move element to sort left */
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (!decreasing) {
            if ((*comp)(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        } else {
              if ((*comp)(v[i], v[left]) > 0) {
                  swap(v, ++last, i);
              }
        }
    }
    swap(v, left, last);     /* move sort element to its final position */
    quicksort(v, left, last - 1, comp);  /* sort left subarray */
    quicksort(v, last + 1, right, comp); /* sort right subarray */
}

int mystrcmp(char *s1, char *s2)
{
    if (directory) {
        while (!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1) {
            ++s1; /* ignore bad characters */
        }
        while (!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2) {
            ++s2; /* ignore bad characters */
        }
    }
    while (fold ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2)) {
        if (*s1 == '\0') {
            return 0;
        }
        ++s1;
        ++s2;
        if (directory) {
            while (!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1) {
                ++s1; /* ignore bad characters */
            }
            while (!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2) {
                ++s2; /* ignore bad characters */
            }
        }
    }
    return fold ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2);
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

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];
    int longline = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            if (line[len - 1] == '\n') {
                line[len - 1] = '\0';  /* delete newline */
                strcpy(p, line);
                if (!longline) {
                    lineptr[nlines++] = p;
                } else {
                    longline = 0;
                }
            } else {
                strcpy(p, line);
                if (!longline) {
                    lineptr[nlines++] = p;
                    longline = 1;
                }
            }
        }
    }
    return nlines;
}

/* get_line: read a line into s, return length */
int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i<lim-1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

char *alloc(int n)
{
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
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
    return;
}
