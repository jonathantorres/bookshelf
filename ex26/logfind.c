#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>

char *logs_path = "/Users/jonathantorres/.logfind";

void search_logfile(char *filepath, char **words, int word_count, bool use_or)
{
    FILE *fp = fopen(filepath, "r");

    if (!fp) {
        fprintf(stderr, "Could not open logfile: %s\n", filepath);
        return;
    }

    char buffer[255];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (use_or == true) {
            for (int i = 0; i < word_count; i++) {
                char *comparison = strstr(buffer, words[i]);
                if (comparison != NULL) {
                    printf("%s", buffer);
                }
            }
        } else {
            int words_found = 0;

            for (int i = 0; i < word_count; i++) {
                char *comparison = strstr(buffer, words[i]);
                if (comparison != NULL) {
                    words_found++;
                }
            }

            if (words_found == word_count) {
                printf("%s", buffer);
            }
        }
    }

    fclose(fp);
}

void check_logs(char **words, int word_count, bool use_or)
{
    FTS *fts_ptr;
    FTSENT *p, *chp;
    int fts_options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR;

    if ((fts_ptr = fts_open(&logs_path, fts_options, NULL)) == NULL) {
        fprintf(stderr, "Error opening logs folder.\n");
        exit(EXIT_FAILURE);
    }

    chp = fts_children(fts_ptr, 0);

    if (chp == NULL) {
        fprintf(stdout, "No logfiles to check.\n");
        exit(EXIT_SUCCESS);
    }

    while ((p = fts_read(fts_ptr)) != NULL) {
        if (p->fts_info == FTS_F) {
            search_logfile(p->fts_path, words, word_count, use_or);
        }
    }

    fts_close(fts_ptr);
}

int main(int argc, char **argv)
{
    bool use_or = false;
    int words_count = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage logfind -o <keywords>\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            use_or = true;
            if (argc <= 2) {
                fprintf(stderr, "Usage logfind -o <keywords>\n");
                exit(EXIT_FAILURE);
            }
        } else {
            words_count++;
        }
    }

    char *words[words_count];
    int words_index = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") != 0) {
            words[words_index] = argv[i];
            words_index++;
        }
    }

    check_logs(words, words_count, use_or);

    return 0;
}
