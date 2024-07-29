#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

void undef(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
unsigned hash(char *s);
char *_strdup(char *s);

int main(void)
{
    struct nlist *lu = install("Jonathan", "def");

    if (!lu) {
        puts("Error installing key into table");
        return 1;
    }

    if (lookup("Jonathan") == NULL) {
        puts("Error! The table lookup should contain the 'Jonathan' key");
        return 1;
    }

    undef("Jonathan");

    if (lookup("Jonathan") != NULL) {
        puts("Error! The table lookup should not contain the 'Jonathan' key");
        return 1;
    }

    puts("Ok");

    return 0;
}

void undef(char *s)
{
    struct nlist *np1, *np2;
    unsigned hashval = hash(s);

    for (np1 = hashtab[hashval], np2 = NULL; np1 != NULL; np2 = np1, np1 = np1->next) {
        if (strcmp(s, np1->name) == 0) {
            free(np1->name);
            free(np1->defn);

            if (np2 == NULL) {
                hashtab[hashval] = np1->next;
            } else {
                np2->next = np1->next;
            }

            free(np1);

            return;
        }
    }
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }

    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));

        if (np == NULL || (np->name = _strdup(name)) == NULL) {
            return NULL;
        }

        hashval          = hash(name);
        np->next         = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *)np->defn);
    }

    if ((np->defn = _strdup(defn)) == NULL) {
        return NULL;
    }

    return np;
}

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; ++s) {
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}

char *_strdup(char *s)
{
    char *p;
    p = (char *)malloc(strlen(s) + 1);

    if (p != NULL) {
        strcpy(p, s);
    }

    return p;
}
