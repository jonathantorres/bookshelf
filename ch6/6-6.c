#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 1000
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist * hashtab[HASHSIZE];

struct nlist * lookup(char * );
struct nlist * install(char * , char * );
int process(void);
int getch(void);
void ungetch(int);
int preproc(void);
int backslash(void);
int comment(void);
int literal(void);
int readword(void);
unsigned hash(char *);
char *_strdup(char *);

int main(void)
{
    int c;
    const int done = 0;
    int status = 1;
    while (!done) {
        while (isspace(c = getch())) {
            putchar(c);
            if (c == '\n') {
                status = 1;
            }
        }
        if (c == '#' && status == 1) {
            status = preproc();
        }
        else if (c == '\\') {
            status = backslash();
        }
        else if (c == '/') {
            status = comment();
        }
        else if (c == '\"') {
            status = literal();
        }
        else if (c == EOF) {
            return 0;
        }
        else if (!isalpha(c) && c != '_') {
            putchar(c);
            status = 0;
        } else {
            ungetch(c);
            status = readword();
        }
        if (status == 2) {
            return 1;
        }
    }
    return 0;
}

int preproc(void)
{
    int c;
    char name[MAXWORD + 1], defn[MAXWORD + 1];
    char * n, * d;

    for (n = name; isalpha(c = getch()) && n - name < MAXWORD; ++n) {
        *n = c;
    }
    *n = '\0';

    if (strcmp(name, "define") == 0) {
        while (isspace(c)) {
            if (c == '\n') {
                putchar(c);
                return 1;
            }
            c = getch();
        }
        for (n = name; (isalnum(c) || c == '_') && n - name < MAXWORD; ++n) {
            * n = c;
            c = getch();
        }
        * n = '\0';

        while (isspace(c)) {
            if (c == '\n') {
                *defn = '\0';
            }
            c = getch();
        }

        for (d = defn; (isalnum(c) || c == '_') && d - defn < MAXWORD; ++d) {
            * d = c;
            c = getch();
        }
        *d = '\0';
        if (install(name, defn) == NULL) {
            return 2;
        }
    } else {
        putchar('#');
        printf("%s", name);
    }

    while (c != '\n') {
        if (c == EOF)
            return EOF;
        putchar(c);
        c = getch();
    }
    putchar(c);
    return 1;
}

int backslash(void)
{
    int c, slash = 1;
    putchar('\\');
    while ((c = getch()) == '\\') {
        slash = !slash;
        putchar(c);
    }

    if (slash) {
        putchar(c);
    }
    else {
        ungetch(c);
    }

    return 0;
}

int comment(void)
{
    int c;
    int after_star = 0;

    putchar('/');

    if ((c = getch()) == '*') {
        putchar(c);
        c = getch();

        while (c != EOF) {
            if (c == '\\') {
                backslash();
                after_star = 0;
            } else if (c == '*') {
                after_star = 1;
                putchar(c);
            } else if (c == '/' && after_star) {
                putchar(c);
                return 0;
            } else {
                after_star = 0;
                putchar(c);
            }
            c = getch();
        }

        if (c == EOF) {
            return EOF;
        }

        putchar(c);
        return 0;
    } else {
        ungetch(c);
        return 0;
    }
}

int literal(void)
{
    int c;
    putchar('\"');
    c = getch();

    while (c != '\"' && c != EOF) {
        if (c == '\\') {
            backslash();
        }
        else {
            putchar(c);
        }
        c = getch();
    }

    if (c == EOF) {
        return EOF;
    }

    putchar(c);
    return 0;
}

int readword(void)
{
    int c;
    char word[MAXWORD];
    char *w;
    struct nlist *node;

    c = getch();
    for (w = word; (isalnum(c) || c == '_') && c != EOF; ++w) {
        * w = c;
        c = getch();
    }
    *w = '\0';
    node = lookup(word);
    if (node == NULL) {
        printf("%s", word);
    }
    else {
        printf("%s", node->defn);
    }
    if (c == EOF) {
        return EOF;
    }
    ungetch(c);
    return 0;
}

struct nlist *lookup(char * s)
{
    struct nlist * np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

struct nlist *install(char * name, char * defn)
{
    struct nlist * np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist * ) malloc(sizeof(*np));
        if (np == NULL || (np->name = _strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void * ) np->defn);
    }
    if ((np->defn = _strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

unsigned hash(char * s)
{
    unsigned hashval;
    for (hashval = 0;* s != '\0'; ++s) {
        hashval = * s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

char *_strdup(char * s)
{
    char * p;
    p = (char * ) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
    return;
}
