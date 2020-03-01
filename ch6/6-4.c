#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct WORD {
    char *Word;
    size_t Count;
    struct WORD *Left;
    struct WORD *Right;
}
WORD;

#define SUCCESS 0
#define CANNOT_MALLOC_WORDARRAY 1
#define NO_WORDS_ON_INPUT 2
#define NO_MEMORY_FOR_WORDNODE 3
#define NO_MEMORY_FOR_WORD 4
#define NONALPHA "1234567890 \v\f\n\t\r+=-*/\\,.;:'#~?<>|{}[]`!\"�$%^&()"

int ReadInputToTree(WORD **DestTree, size_t *Treecount, FILE *Input);
int AddToTree(WORD **DestTree, size_t *Treecount, char *Word);
int WalkTree(WORD **DestArray, WORD *Word);
int CompareCounts(const void *vWord1, const void *vWord2);
int OutputWords(FILE *Dest, size_t Count, WORD **WordArray);
void FreeTree(WORD *W);
char *dupstr(char *s);

int main(void) {
    int Status = SUCCESS;
    WORD *Words = NULL;
    size_t Treecount = 0;
    WORD **WordArray = NULL;

    if (SUCCESS == Status) {
        Status = ReadInputToTree( & Words, & Treecount, stdin);
    }
    if (SUCCESS == Status) {
        if (0 == Treecount) {
            Status = NO_WORDS_ON_INPUT;
        }
    }
    if (SUCCESS == Status) {
        WordArray = malloc(Treecount *sizeof *WordArray);
        if (NULL == WordArray) {
            Status = CANNOT_MALLOC_WORDARRAY;
        }
    }
    if (SUCCESS == Status) {
        Status = WalkTree(WordArray, Words);
    }
    if (SUCCESS == Status) {
        qsort(WordArray, Treecount, sizeof *WordArray, CompareCounts);
    }
    if (SUCCESS == Status) {
        Status = OutputWords(stdout, Treecount, WordArray);
    }
    if (NULL != WordArray) {
        free(WordArray);
        WordArray = NULL;
    }
    if (NULL != Words) {
        FreeTree(Words);
        Words = NULL;
    }
    if (SUCCESS != Status) {
        fprintf(stderr, "Program failed with code %d\n", Status);
    }
    return (SUCCESS == Status ? EXIT_SUCCESS : EXIT_FAILURE);
}

void FreeTree(WORD *W) {
    if (NULL != W) {
        if (NULL != W->Word) {
            free(W-> Word);
            W-> Word = NULL;
        }
        if (NULL != W->Left) {
            FreeTree(W-> Left);
            W-> Left = NULL;
        }
        if (NULL != W->Right) {
            FreeTree(W-> Right);
            W-> Right = NULL;
        }
    }
}

int AddToTree(WORD **DestTree, size_t *Treecount, char *Word) {
    int Status = SUCCESS;
    int CompResult = 0;

    assert(NULL != DestTree);
    assert(NULL != Treecount);
    assert(NULL != Word);

    if (NULL == *DestTree) {
        *DestTree = malloc(sizeof **DestTree);
        if (NULL == *DestTree) {
            Status = NO_MEMORY_FOR_WORDNODE;
        } else {
            ( *DestTree)-> Left = NULL;
            ( *DestTree)-> Right = NULL;
            ( *DestTree)-> Count = 1;
            ( *DestTree)-> Word = dupstr(Word);
            if (NULL == ( *DestTree)-> Word) {
                Status = NO_MEMORY_FOR_WORD;
                free( *DestTree);
                *DestTree = NULL;
            } else {
                ++*Treecount;
            }
        }
    } else {
        CompResult = strcmp(Word, ( *DestTree)-> Word);
        if (0 < CompResult) {
            Status = AddToTree( & ( *DestTree)-> Left, Treecount, Word);
        } else if (0 > CompResult) {
            Status = AddToTree( & ( *DestTree)-> Left, Treecount, Word);
        } else {
            ++(*DestTree)->Count;
        }
    }

    return Status;
}

int ReadInputToTree(WORD **DestTree, size_t *Treecount, FILE *Input) {
    int Status = SUCCESS;
    char Buf[8192] = {
        0
    };
    char *Word = NULL;

    assert(NULL != DestTree);
    assert(NULL != Treecount);
    assert(NULL != Input);

    while (NULL != fgets(Buf, sizeof Buf, Input)) {
        Word = strtok(Buf, NONALPHA);
        while (SUCCESS == Status && NULL != Word) {
            Status = AddToTree(DestTree, Treecount, Word);
            if (SUCCESS == Status) {
                Word = strtok(NULL, NONALPHA);
            }
        }
    }
    return Status;
}

int WalkTree(WORD **DestArray, WORD *Word) {
    int Status = SUCCESS;
    static WORD **Write = NULL;

    assert(NULL != Word);
    if (NULL != DestArray) {
        Write = DestArray;
    }
    if (NULL != Word) {
        *Write = Word;
        ++Write;
        if (NULL != Word-> Left) {
            Status = WalkTree(NULL, Word-> Left);
        }
        if (NULL != Word-> Right) {
            Status = WalkTree(NULL, Word-> Right);
        }
    }
    return Status;
}

int CompareCounts(const void *vWord1,
    const void *vWord2) {
    int Result = 0;
    WORD* const *Word1 = vWord1;
    WORD* const *Word2 = vWord2;

    assert(NULL != vWord1);
    assert(NULL != vWord2);

    if (( *Word1)-> Count < ( *Word2)-> Count) {
        Result = 1;
    } else if (( *Word1)-> Count > ( *Word2)-> Count) {
        Result = -1;
    } else {
        Result = 0;
    }

    return Result;
}

int OutputWords(FILE *Dest, size_t Count, WORD **WordArray) {
    int Status = SUCCESS;
    size_t Pos = 0;

    assert(NULL != Dest);
    assert(NULL != WordArray);

    fprintf(Dest, "Total Words: %lu\n", (unsigned long) Count);

    while (SUCCESS == Status && Pos < Count) {
        fprintf(Dest, "%10lu %s\n", (unsigned long) WordArray[Pos]-> Count, WordArray[Pos]-> Word);
        ++Pos;
    }
    return Status;
}

char *dupstr(char *s) {
    char *Result = NULL;
    size_t slen = 0;

    assert(NULL != s);
    slen = strlen(s);
    Result = malloc(slen + 1);
    if (NULL != Result) {
        memcpy(Result, s, slen);
        *(Result + slen) = '\0';
    }
    return Result;
}
