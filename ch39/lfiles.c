#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define PATHLEN 256

bool print_contents(const char *full_path, bool use_flag);
void print_files(const char *cur_path, bool use_flag);

int main(int argc, char const *argv[])
{
    bool use_flag = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp("-l", argv[i]) == 0) {
            use_flag = true;
        }
    }
    if (argc == 2 && use_flag) {
        print_files(".", use_flag);
        exit(EXIT_SUCCESS);
    } else if (argc == 1) {
        print_files(".", false);
        exit(EXIT_SUCCESS);
    } else if (argc > 3) {
        puts("usage: ./lfiles [filename] -l");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp("-l", argv[i]) != 0) {
            print_files(argv[i], use_flag);
        }
    }
    return 0;
}

bool print_contents(const char *full_path, bool use_flag)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(full_path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0) {
                continue;
            }
            if (use_flag) {
                struct stat st;
                int rc = stat(ent->d_name, &st);
                if (rc == 0) {
                    printf("%s %d %d %d\n", ent->d_name, st.st_uid, st.st_gid, st.st_mode);
                } else {
                    printf("Error reading stats for file %s\n", ent->d_name);
                    continue;
                }
            } else {
                printf("%s\n", ent->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Error reading directory");
        return false;
    }
    return true;
}

void print_files(const char *cur_path, bool use_flag)
{
    char *path = malloc(PATHLEN);
    if (!path) {
        puts("Fatal error! No memory!");
        exit(EXIT_FAILURE);
    }

    // using current dir
    if (strcmp(cur_path, ".") == 0) {
        char *full_path = getcwd(path, PATHLEN);
        if (!full_path) {
            perror("Error reading path");
            free(path);
            exit(EXIT_FAILURE);
        }
        bool rc = print_contents(full_path, use_flag);
        if (!rc) {
            free(path);
            exit(EXIT_FAILURE);
        }
        free(path);
        return;
    }

    bool rc = print_contents(cur_path, use_flag);
    if (!rc) {
        free(path);
        exit(EXIT_FAILURE);
    }

    // use specified path
    free(path);
}
