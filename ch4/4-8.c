#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100    // max size of operand or operator
#define MAXOP 100    // max size of operand or operator
#define NUMBER '0' // signal that a number wes found

char buf[BUFSIZE];
int bufp = 0;
int flag;
int last;

int getop(char s[]);
int getch(void);
void ungetch(int c);
void ungets(char s[]);
void ingetch(int);

int main(void)
{
    int type;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        printf("%c", type);
    }
    return 0;
}

int getch(void)
{
    if (!flag) {
        return getchar();
    } else {
        flag = 0;
        return last;
    }
}

void ungetch(int c)
{
    last = c;
    flag = 1;
}

void ungets(char s[])
{
    int i = strlen(s);
    while (i > 0) {
        ungetch(s[--i]);
    }
}

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {

    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {
            //
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch())) {

        }
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}
