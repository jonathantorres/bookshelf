#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct word_t {
    char *word;
    size_t count;
    struct word_t *left;
    struct word_t *right;
} word_t;

#define SUCCESS 0
#define CANNOT_MALLOC_WORDARRAY 1
#define NO_WORDS_ON_INPUT 2
#define NO_MEMORY_FOR_WORDNODE 3
#define NO_MEMORY_FOR_WORD 4
#define NONALPHA "1234567890 \v\f\n\t\r+=-*/\\,.;:'#~?<>|{}[]`!\"�$%^&()"

int read_input_to_tree(word_t **dest_tree, size_t *tree_count, FILE *input);
int add_to_tree(word_t **dest_tree, size_t *tree_count, char *word);
int walk_tree(word_t **dest_array, word_t *word);
int compare_counts(const void *w1, const void *w2);
int output_words(FILE *dest, size_t Count, word_t **WordArray);
void free_tree(word_t *w);
char *dupstr(char *s);

int main(void)
{
    int status          = SUCCESS;
    word_t *words       = NULL;
    size_t tree_count   = 0;
    word_t **word_array = NULL;

    if (SUCCESS == status) {
        status = read_input_to_tree(&words, &tree_count, stdin);
    }
    if (SUCCESS == status) {
        if (0 == tree_count) {
            status = NO_WORDS_ON_INPUT;
        }
    }
    if (SUCCESS == status) {
        word_array = malloc(tree_count * sizeof *word_array);
        if (NULL == word_array) {
            status = CANNOT_MALLOC_WORDARRAY;
        }
    }
    if (SUCCESS == status) {
        status = walk_tree(word_array, words);
    }
    if (SUCCESS == status) {
        qsort(word_array, tree_count, sizeof *word_array, compare_counts);
    }
    if (SUCCESS == status) {
        status = output_words(stdout, tree_count, word_array);
    }
    if (NULL != word_array) {
        free(word_array);
        word_array = NULL;
    }
    if (NULL != words) {
        free_tree(words);
        words = NULL;
    }
    if (SUCCESS != status) {
        fprintf(stderr, "Program failed with code %d\n", status);
    }
    return (SUCCESS == status ? EXIT_SUCCESS : EXIT_FAILURE);
}

void free_tree(word_t *w)
{
    if (NULL != w) {
        if (NULL != w->word) {
            free(w->word);
            w->word = NULL;
        }
        if (NULL != w->left) {
            free_tree(w->left);
            w->left = NULL;
        }
        if (NULL != w->right) {
            free_tree(w->right);
            w->right = NULL;
        }
    }
}

int add_to_tree(word_t **dest_tree, size_t *tree_count, char *word)
{
    int status      = SUCCESS;
    int comp_result = 0;

    assert(NULL != dest_tree);
    assert(NULL != tree_count);
    assert(NULL != word);

    if (NULL == *dest_tree) {
        *dest_tree = malloc(sizeof **dest_tree);
        if (NULL == *dest_tree) {
            status = NO_MEMORY_FOR_WORDNODE;
        } else {
            (*dest_tree)->left = NULL;
            (*dest_tree)->right = NULL;
            (*dest_tree)->count = 1;
            (*dest_tree)->word = dupstr(word);
            if (NULL == (*dest_tree)->word) {
                status = NO_MEMORY_FOR_WORD;
                free(*dest_tree);
                *dest_tree = NULL;
            } else {
                ++*tree_count;
            }
        }
    } else {
        comp_result = strcmp(word, (*dest_tree)->word);
        if (0 < comp_result) {
            status = add_to_tree(&(*dest_tree)->left, tree_count, word);
        } else if (0 > comp_result) {
            status = add_to_tree(&(*dest_tree)->left, tree_count, word);
        } else {
            ++(*dest_tree)->count;
        }
    }

    return status;
}

int read_input_to_tree(word_t **dest_tree, size_t *tree_count, FILE *input)
{
    int status     = SUCCESS;
    char buf[8192] = {0};
    char *word     = NULL;

    assert(NULL != dest_tree);
    assert(NULL != tree_count);
    assert(NULL != input);

    while (fgets(buf, sizeof(buf), input) != NULL) {
        word = strtok(buf, NONALPHA);
        while (SUCCESS == status && NULL != word) {
            status = add_to_tree(dest_tree, tree_count, word);
            if (SUCCESS == status) {
                word = strtok(NULL, NONALPHA);
            }
        }
    }
    return status;
}

int walk_tree(word_t **dest_array, word_t *word)
{
    int status            = SUCCESS;
    static word_t **write = NULL;

    assert(NULL != word);

    if (dest_array != NULL) {
        write = dest_array;
    }
    if (word != NULL) {
        *write = word;
        ++write;
        if (word->left != NULL) {
            status = walk_tree(NULL, word->left);
        }
        if (word->right != NULL) {
            status = walk_tree(NULL, word->right);
        }
    }
    return status;
}

int compare_counts(const void *w1, const void *w2)
{
    int res              = 0;
    word_t* const *word1 = w1;
    word_t* const *word2 = w2;

    assert(NULL != w1);
    assert(NULL != w2);

    if ((*word1)->count < (*word2)->count) {
        res = 1;
    } else if ((*word1)->count > (*word2)->count) {
        res = -1;
    } else {
        res = 0;
    }

    return res;
}

int output_words(FILE *dest, size_t count, word_t **word_array)
{
    int status = SUCCESS;
    size_t pos = 0;

    assert(NULL != dest);
    assert(NULL != word_array);

    fprintf(dest, "Total Words: %lu\n", (unsigned long) count);

    while (SUCCESS == status && pos < count) {
        fprintf(dest, "%10lu %s\n", (unsigned long) word_array[pos]->count, word_array[pos]->word);
        ++pos;
    }
    return status;
}

char *dupstr(char *s)
{
    char *res   = NULL;
    size_t slen = 0;

    assert(NULL != s);

    slen = strlen(s);
    res  = malloc(slen + 1);
    if (NULL != res) {
        memcpy(res, s, slen);
        *(res + slen) = '\0';
    }
    return res;
}
