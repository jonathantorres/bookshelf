#include <stdio.h>

#define MAXLINE 1024
#define TABSIZE 4

int getline(char line[], int maxline);
void entab(char line[], char nline[], int len);
void detab(char line[], char nline[], int len);

int main(void)
{
    int len;
    char line[MAXLINE];
    char nline[MAXLINE];

    for (int i = 0; i < MAXLINE; i++) {
        line[i]  = 0;
        nline[i] = 0;
    }

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 0) {
            entab(line, nline, len);
            detab(line, nline, len);
            printf("%s", line);
        }
    }

    return 0;
}

void entab(char line[], char nline[], int maxline)
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
            nline[j++] = '\t';
        } else {
            nline[j++] = c;
        }

        if (c != ' ') {
            ns = 0;
        }
    }

    nline[j] = '\0';
}

void detab(char line[], char nline[], int maxline)
{
    int i, j;

    j = 0;

    for (i = 0; i < maxline; ++i) {
        char c = line[i];

        if (c == '\t') {
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
