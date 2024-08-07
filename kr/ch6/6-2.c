#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct var_group {
    char *word;
} var_arr[] = {{"char"}, {"double"}, {"float"}, {"int"}, {"long"}, {"struct"}, {"unsigned"}};

#define DEFAULT  6
#define MAXWORD  512
#define MAXVAR   512
#define VAR_SIZE (sizeof(var_arr) / sizeof(var_arr[0]))
#define BUFSIZE  1024

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int vg_index = 0;
char *vgroup[MAXVAR];

struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
int getword(char *word, int lim);
int binsearch(char *word, struct var_group var_arr[], int n);
void getvar(int n);
struct tnode *talloc(void);
int getch(void);
void ungetch(int c);
char *_strdup(char *s);

int main(int argc, char *argv[])
{
    int index, n;
    struct tnode *root;

    if (argc == 1) {
        n = DEFAULT;
    } else {
        while (!isdigit(*++argv[0])) {
            ;
        }

        n = atoi(*argv);
    }

    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if (((index = binsearch(word, var_arr, VAR_SIZE)) >= 0) && vg_index < MAXVAR) {
                getvar(n);
            }
        }
    }

    vgroup[vg_index] = NULL;
    root             = NULL;

    for (index = 0; index < vg_index - 1; index++) {
        root = addtree(root, vgroup[index]);
    }

    treeprint(root);

    return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p        = talloc();
        p->word  = _strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }

    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
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

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';

    return word[0];
}

int binsearch(char *word, struct var_group var_arr[], int n)
{
    int cond;
    int low, high, mid;
    low  = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, var_arr[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

void getvar(int n)
{
    int c;
    int i = 0;
    char word[MAXWORD];

    while (isspace(c = getch())) {
        ;
    }

    ungetch(c);

    while ((c = getch()) != EOF) {
        if (isalnum(c) || c == '_') {
            word[i++] = c;
        } else {
            word[i] = '\0';

            if (i >= n && binsearch(word, var_arr, VAR_SIZE) < 0) {
                vgroup[vg_index] = malloc(i);
                strcpy(vgroup[vg_index], word);
                ++vg_index;
            }

            i = 0;

            while (isspace(c = getch())) {
                ;
            }

            if (c != ',') {
                ungetch(c);
                break;
            }
        }
    }
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

char buf[BUFSIZE];
int bufp = 0;

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
}
