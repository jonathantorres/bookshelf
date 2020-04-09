#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define LINE_LEN 2048

bool print_file(const char *filename, int lines_to_disp);

int main(int argc, char const *argv[])
{
    int lines_to_disp = 0;
    if (argc < 2) {
        puts("usage: ./tail [filename]");
        exit(EXIT_FAILURE);
    }

    int i = 1;
    if (strcmp("-n", argv[1]) == 0) {
        lines_to_disp = atoi(argv[2]);
        i += 2;
    }
    for (; i < argc; i++) {
        if (!print_file(argv[i], lines_to_disp)) {
            perror("File error: ");
        }
    }
    return 0;
}


bool print_file(const char *filename, int lines_to_disp)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return false;
    }
    printf(">>>> %s <<<<<\n", filename);
    // show last 5 lines by default
    int last_lines = (lines_to_disp == 0) ? 5 : lines_to_disp;
    int total_lines = 0;
    char *linebuf = NULL;
    size_t linecap = LINE_LEN;

    int lsize = getline(&linebuf, &linecap, fp);
    while (lsize >= 0) {
        total_lines++;
        lsize = getline(&linebuf, &linecap, fp);
    }
    rewind(fp);

    if (last_lines >= total_lines) {
        last_lines = total_lines;
    }
    lsize = getline(&linebuf, &linecap, fp);
    int cur_line = 1;
    while (lsize >= 0) {
        if ((total_lines - last_lines) < cur_line) {
            printf("%s", linebuf);
        }
        lsize = getline(&linebuf, &linecap, fp);
        cur_line++;
    }
    printf("\n");
    fclose(fp);
    return true;
}
