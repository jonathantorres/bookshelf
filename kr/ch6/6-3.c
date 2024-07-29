#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 8192

struct linelist {
    struct linelist *next;
    int line;
};

struct wordtree {
    char *word;
    struct linelist *firstline;
    struct wordtree *left;
    struct wordtree *right;
};

struct wordtree *addword(struct wordtree **node, char *word, int line);
void printlist(struct linelist *list);
void printtree(struct wordtree *node);
struct linelist *addlink(int line);
void deletelist(struct linelist *listnode);
void deleteword(struct wordtree **node);
char *char_in_string(char *s, int c);
int i_strcmp(const char *s, const char *t);
char *tokenise(char **s, char *delims);
char *dupstr(char *s);
int noiseword(char *s);
char *getline(char *s, int n, FILE *fp);

int main(void)
{
    static char buffer[MAXLINE] = {0};
    char *s                     = NULL;
    char *word                  = NULL;
    int line                    = 0;
    int end                     = 0;
    struct wordtree *tree       = NULL;
    char *delims                = " \t\n\r\a\f\v!\"%^&*()_=+{}[]\\|/,.<>:;#~?";

    while (!end && getline(buffer, sizeof(buffer), stdin) != NULL) {
        ++line;
        s = buffer;

        while (!end && (word = tokenise(&s, delims)) != NULL) {
            if (!noiseword(word)) {
                if (addword(&tree, word, line) == NULL) {
                    printf("Not enough memory to add the word...Exiting.\n");
                    end = 1;
                }
            }
        }
    }

    if (!end) {
        printf("%18s  Line Numbers\n", "Word");
        printtree(tree);
    }

    deleteword(&tree);

    return 0;
}

struct linelist *addlink(int line)
{
    struct linelist *new = malloc(sizeof(struct linelist));

    if (new != NULL) {
        new->line = line;
        new->next = NULL;
    }

    return new;
}

void deletelist(struct linelist *listnode)
{
    if (listnode != NULL) {
        deletelist(listnode->next);
        free(listnode);
    }
}

void deleteword(struct wordtree **node)
{
    struct wordtree *tmp = NULL;

    if (node != NULL) {
        if (*node) {
            if ((*node)->right != NULL) {
                tmp = *node;
                deleteword(&tmp->right);
            }

            if ((*node)->left != NULL) {
                tmp = *node;
                deleteword(&tmp->left);
            }

            if ((*node)->word != NULL) {
                free((*node)->word);
            }

            if ((*node)->firstline != NULL) {
                deletelist((*node)->firstline);
            }

            free(*node);

            *node = NULL;
        }
    }
}

struct wordtree *addword(struct wordtree **node, char *word, int line)
{
    struct wordtree *wordloc = NULL;
    struct linelist *newline = NULL;
    struct wordtree *tmp     = NULL;
    int diff                 = 0;

    if (node != NULL && word != NULL) {
        if (*node == NULL) {
            *node = malloc(sizeof(**node));

            if (NULL != *node) {
                (*node)->left  = NULL;
                (*node)->right = NULL;
                (*node)->word  = dupstr(word);
                if ((*node)->word != NULL) {
                    (*node)->firstline = addlink(line);
                    if ((*node)->firstline != NULL) {
                        wordloc = *node;
                    }
                }
            }
        } else {
            diff = i_strcmp((*node)->word, word);

            if (diff == 0) {
                newline = addlink(line);
                if (newline != NULL) {
                    wordloc            = *node;
                    newline->next      = (*node)->firstline;
                    (*node)->firstline = newline;
                }
            } else if (0 < diff) {
                tmp     = *node;
                wordloc = addword(&tmp->left, word, line);
            } else {
                tmp     = *node;
                wordloc = addword(&tmp->right, word, line);
            }
        }
    }

    if (wordloc == NULL) {
        deleteword(node);
    }

    return wordloc;
}

char *char_in_string(char *s, int c)
{
    char *p = NULL;

    if (s != NULL) {
        if (c != '\0') {
            while (*s != '\0' && *s != c) {
                ++s;
            }

            if (*s == c) {
                p = s;
            }
        }
    }

    return p;
}

char *tokenise(char **s, char *delims)
{
    char *p = NULL;
    char *q = NULL;

    if (s != NULL && *s && delims != NULL) {
        while (NULL != char_in_string(delims, **s)) {
            ++*s;
        }

        if (**s != '\0') {
            q = *s + 1;
            p = *s;

            while (*q != '\0' && NULL == char_in_string(delims, *q)) {
                ++q;
            }

            *s = q + (*q != '\0');
            *q = '\0';
        }
    }

    return p;
}

int noiseword(char *s)
{
    int found    = 0;
    int end      = 0;
    char *list[] = {"a",  "an",  "and", "be",  "but", "by",  "he",   "I",  "is",
                    "it", "off", "on",  "she", "so",  "the", "they", "you"};
    int top      = sizeof(list) / sizeof(list[0]) - 1;
    int bottom   = 0;
    int guess    = top / 2;
    int diff     = 0;

    if (s != NULL) {
        while (!found && !end) {
            diff = i_strcmp(list[guess], s);

            if (0 == diff) {
                found = 1;
            } else if (0 < diff) {
                top = guess - 1;
            } else {
                bottom = guess + 1;
            }

            if (top < bottom) {
                end = 1;
            } else {
                guess = (top + bottom) / 2;
            }
        }
    }

    return found;
}

int i_strcmp(const char *s, const char *t)
{
    int diff = 0;
    char cs  = 0;
    char ct  = 0;

    while (diff == 0 && *s != '\0' && *t != '\0') {
        cs = tolower((unsigned char)*s);
        ct = tolower((unsigned char)*t);

        if (cs < ct) {
            diff = -1;
        } else if (cs > ct) {
            diff = 1;
        }

        ++s;
        ++t;
    }

    if (diff == 0 && *s != *t) {
        if (*s == '\0') {
            diff = -1;
        } else {
            diff = 1;
        }
    }

    return diff;
}

void printlist(struct linelist *list)
{
    if (list != NULL) {
        printlist(list->next);
        printf("%6d ", list->line);
    }
}

void printtree(struct wordtree *node)
{
    if (node != NULL) {
        printtree(node->left);
        printf("%18s  ", node->word);
        printlist(node->firstline);
        printf("\n");
        printtree(node->right);
    }
}

char *dupstr(char *s)
{
    char *p = NULL;

    if (s != NULL) {
        p = malloc(strlen(s) + 1);

        if (p) {
            strcpy(p, s);
        }
    }

    return p;
}

char *getline(char *s, int n, FILE *fp)
{
    int c    = 0;
    int done = 0;
    char *p  = s;

    while (!done && --n > 0 && (c = getc(fp)) != EOF) {
        if ((*p++ = c) == '\n') {
            done = 1;
        }
    }

    *p = '\0';

    if (EOF == c && p == s) {
        p = NULL;
    } else {
        p = s;
    }

    return p;
}
