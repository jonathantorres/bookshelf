#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTOR   5120
#define MAXLEN    1024
#define ALLOCSIZE 50000

int getline(char *s, int lim);
char *alloc(int n);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int field_index(int fld, char *s);
int numcmp_increase(char *s1, char *s2);
int numcmp_decrease(char *s1, char *s2);
int my_strcmp_decrease(char *s1, char *s2);
int my_strcmp_increase(char *s1, char *s2);
int read_input(char *s);
char *fillfld(char *s);
void swap(void *v[], int i, int j);

char *lineptr[MAXLEN];
int decrease = 0;
int fold     = 0;
int dir      = 0;
int numeric  = 0;
int flag     = 0;
int field    = 0;

int main(int argc, char *argv[])
{
    int nlines;
    int i, j;
    unsigned int uargc;

    uargc = argc;
    for (i = uargc - 1, j = 1; i > 0; i--, j++) {
        if (read_input(argv[j]) != 0) {
            exit(EXIT_FAILURE);
        }
    }

    j = 1;

    if ((nlines = readlines(lineptr, MAXLEN)) >= 0) {
        while (--uargc) {
            read_input(argv[j]);

            if (decrease == 0) {
                qsort2((void **)lineptr, 0, nlines - 1,
                       (int (*)(void *, void *))(numeric ? numcmp_increase : my_strcmp_increase));
            } else {
                qsort2((void **)lineptr, 0, nlines - 1,
                       (int (*)(void *, void *))(numeric ? numcmp_decrease : my_strcmp_decrease));
            }

            ++j;
            flag = 0;
        }

        writelines(lineptr, nlines);

        return 0;
    }

    printf("input too big to sort\n");

    return 1;
}

int read_input(char *s)
{
    decrease = 0;
    fold     = 0;
    dir      = 0;
    numeric  = 0;

    if (s[0] != '-') {
        printf("usage: sort -dfnr\n");
        return 1;
    }

    while (*s) {
        ++s;
        switch (*s) {
            case 'n':
                numeric = 1;
                break;
            case 'f':
                fold = 1;
                break;
            case 'r':
                decrease = 1;
                break;
            case 'd':
                dir = 1;
                break;
            case 'c':
                if (flag == 0) {
                    s    = fillfld(s);
                    flag = 1;
                } else {
                    return 0;
                }
                break;
            case '\0':
                break;
            default:
                printf("usage: sort -dfnr\n");
                return 1;
        }
    }

    return 0;
}

char *fillfld(char *s)
{
    int i;
    i = 0;

    while (*s) {
        ++s;

        if ((!(isdigit(*s))) && *s != '-') {
            printf("Wrong args to field\n");
            exit(EXIT_FAILURE);
        }

        if (*s == '-') {
            ++s;
        }

        if (isdigit(*s)) {
            while (isdigit(*s)) {
                field = field * 10 + (*s - '0');
                ++s;
            }
            ++i;
        }
    }

    return s;
}

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        last = left;
    }

    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort2(v, left, last - 1, comp);
    qsort2(v, last + 1, right, comp);
}

int numcmp_decrease(char *s1, char *s2)
{
    int fld_idx_s1 = 0, fld_idx_s2 = 0;
    double v1 = 0, v2 = 0;

    if (flag != 0 && field != 0) {
        fld_idx_s1 = field_index(field, s1);
        fld_idx_s2 = field_index(field, s2);
    }

    v1 = atof(s1 + fld_idx_s1);
    v2 = atof(s2 + fld_idx_s2);

    if (v1 == v2) {
        return 0;
    }

    if (v1 < v2) {
        return 1;
    } else {
        return -1;
    }
}

int numcmp_increase(char *s1, char *s2)
{
    int fld_idx_s1 = 0, fld_idx_s2 = 0;
    double v1, v2;

    if (flag != 0 && field != 0) {
        fld_idx_s1 = field_index(field, s1);
        fld_idx_s2 = field_index(field, s2);
    }

    v1 = atof(s1 + fld_idx_s1);
    v2 = atof(s2 + fld_idx_s2);

    if (v1 == v2) {
        return 0;
    }

    if (v1 < v2) {
        return -1;
    } else {
        return 1;
    }
}

int my_strcmp_decrease(char *s1, char *s2)
{
    int fld_idx_s1 = 0, fld_idx_s2 = 0;

    if (flag != 0 && field != 0) {
        fld_idx_s1 = field_index(field, s1);
        fld_idx_s2 = field_index(field, s2);
    }

    while (s1[fld_idx_s1] == s2[fld_idx_s2]) {
        ++fld_idx_s1;
        ++fld_idx_s2;
    }

    if (s1[fld_idx_s1] == '\0' && s2[fld_idx_s2] == '\0') {
        if (dir == 0) {
            return s1 - s2;
        } else if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) &&
                   (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
            return s1 - s2;
        } else {
            exit(EXIT_FAILURE);
        }
    }

    if (fold == 0 && dir == 0) {
        if (s1[fld_idx_s1] < s2[fld_idx_s2]) {
            return 1;
        } else {
            return -1;
        }
    } else if (fold == 0 && dir == 1) {
        if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) &&
            (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
            if (s1[fld_idx_s1] < s2[fld_idx_s2]) {
                return 1;
            } else {
                return -1;
            }
        } else {
            exit(EXIT_FAILURE);
        }
    } else if (fold == 1 && dir == 0) {
        return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s2])) ? 1 : -1;
    } else {
        if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) &&
            (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
            return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s1])) ? 1 : -1;
        } else {
            exit(EXIT_FAILURE);
        }
    }
}

int my_strcmp_increase(char *s1, char *s2)
{
    int fld_idx_s1 = 0, fld_idx_s2 = 0;

    if (flag != 0 && field != 0) {
        fld_idx_s1 = field_index(field, s1);
        fld_idx_s2 = field_index(field, s2);
    }

    while (s1[fld_idx_s1] == s2[fld_idx_s2]) {
        ++fld_idx_s1;
        ++fld_idx_s2;
    }

    if (s1[fld_idx_s1] == '\0' && s2[fld_idx_s2] == '\0') {
        if (dir == 0) {
            return s1 - s2;
        } else if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) &&
                   (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
            return s1 - s2;
        } else {
            exit(EXIT_FAILURE);
        }
    }

    if (fold == 0 && dir == 0) {
        if (s1[fld_idx_s1] < s2[fld_idx_s2]) {
            return -1;
        } else {
            return 1;
        }
    } else if (fold == 0 && dir == 1) {
        if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) &&
            (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
            if (s1[fld_idx_s1] < s2[fld_idx_s2]) {
                return -1;
            } else {
                return 1;
            }
        } else {
            exit(EXIT_FAILURE);
        }
    } else if (fold == 1 && dir == 0) {
        return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s2])) ? -1 : 1;
    } else {
        if ((isalnum(s1[fld_idx_s1]) || isspace(s1[fld_idx_s1])) &&
            (isalnum(s2[fld_idx_s2]) || isspace(s2[fld_idx_s2]))) {
            return (tolower(s1[fld_idx_s1]) < tolower(s2[fld_idx_s1])) ? -1 : 1;
        } else {
            exit(EXIT_FAILURE);
        }
    }
}

int field_index(int fld, char *s)
{
    int i, count_words = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (isspace(s[i])) {
            ++count_words;
        }

        if (count_words == fld) {
            return i + 1;
        }
    }

    return 0;
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

    lineptr[nlines] = NULL;

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
