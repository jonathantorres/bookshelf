#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD  512
#define BUFFSIZE 1024
#define NKEYS    (sizeof(keytab) / sizeof(keytab[0]))

struct key {
    char *word;
    int count;
} keytab[] = {
    {
        "auto",
        0,
    },
    {
        "break",
        0,
    },
    {
        "case",
        0,
    },
    {
        "char",
        0,
    },
    {
        "continue",
        0,
    },
    {
        "unsigned",
        0,
    },
    {
        "void",
        0,
    },
    {
        "volatile",
        0,
    },
    {"while", 0},
};

int getch(void);
void ungetch(int c);
int acceptable(char c);
int getword(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);

int main(void)
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }

    for (n = 0; n < (int)NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }

    return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low  = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int acceptable(char c)
{
    return ((c == '_') || (c == '"') || (c == '#') || (c == '/') || isalnum(c));
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch())) {
        ;
    }

    if (c != EOF) {
        *w++ = c;
    }

    if (!acceptable(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!acceptable(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';

    return word[0];
}

char buf[BUFFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
