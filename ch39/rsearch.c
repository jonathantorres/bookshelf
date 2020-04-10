#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

bool print_files(const char *location);

int main(int argc, char const *argv[])
{
    if (argc == 2) {
        if (print_files(argv[1])) {
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    } else if (argc == 1) {
        if (print_files(".")) {
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    puts("usage: ./rsearch [directory]");
    return 1;
}

bool print_files(const char *location)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(location)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0) {
                continue;
            }
            struct stat st;
            int rc = stat(ent->d_name, &st);
            if (rc == 0) {
                printf("%s %d %d %d\n", ent->d_name, st.st_uid, st.st_gid, st.st_mode);
                if (ent->d_type == DT_DIR) {
                    print_files(ent->d_name);
                }
            } else {
                printf("Error reading stats for file %s\n", ent->d_name);
                continue;
            }
        }
        closedir(dir);
    } else {
        perror("Error reading directory");
        return false;
    }
    return true;
}
