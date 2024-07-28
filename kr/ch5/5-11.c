#include <stdio.h>

#define MAXLINE 1024
#define TABSIZE 4

int getline(char line[], int maxline);
void entab(char line[], char nline[], int maxline, char ts);
void detab(char line[], char nline[], int maxline, char ts);

int main(int argc, char **argv)
{
    int len;
    char line[MAXLINE];
    char nline[MAXLINE];
    char ts = '\t';

    for (int i = 0; i < MAXLINE; i++) {
        line[i]  = 0;
        nline[i] = 0;
    }

    if (argc > 1) {
        ts = argv[1][0];
    }

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 0) {
            entab(line, nline, len, ts);
            detab(line, nline, len, ts);
            printf("%s", nline);
        }
    }

    return 0;
}

void entab(char line[], char nline[], int maxline, char ts)
{
    int i, j, ns;
    j  = 0;
    ns = 0;

    for (i = 0; i < maxline; ++i) {
        char c = line[i];

        if (c == ' ') {
            ns++;
        }

        if (c == ' ' && ns == TABSIZE) {
            ns         = 0;
            j          = j - (TABSIZE - 1);
            nline[j++] = ts;
        } else {
            nline[j++] = c;
        }

        if (c != ' ') {
            ns = 0;
        }
    }

    nline[j] = '\0';
}

void detab(char line[], char nline[], int maxline, char ts)
{
    int i, j;

    j = 0;

    for (i = 0; i < maxline; ++i) {
        char c = line[i];

        if (c == ts) {
            for (int k = 0; k < TABSIZE; ++k) {
                nline[j++] = ' ';
            }
        } else {
            nline[j++] = c;
        }
    }

    nline[j] = '\0';
}

int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
