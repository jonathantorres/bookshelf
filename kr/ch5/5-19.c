#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 512
#define BUFSIZE  1024

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

int posttoken(void);
int gettoken(void);
void ungetch(int c);
int getch(void);

int tokentype;
int pretoken = NO;
char token[MAXTOKEN];
char out[BUFSIZE];

int main(void)
{
    int type;
    char temp[BUFSIZE * 2];

    while (gettoken() != EOF) {
        strcpy(out, token);

        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            } else if (type == '*') {
                if ((type = posttoken()) == PARENS || type == BRACKETS) {
                    sprintf(temp, "(*%s)", out);
                } else {
                    sprintf(temp, "*%s", out);
                }
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
        }

        printf("%s\n", out);
    }

    return 0;
}

int gettoken(void)
{
    int c;
    char *p = token;

    if (pretoken == YES) {
        pretoken = NO;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t') {
        ;
    }

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';) {
            ;
        }

        *p               = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());) {
            *p++ = c;
        }

        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

int posttoken(void)
{
    int nexttype;
    nexttype = gettoken();
    pretoken = YES;

    return nexttype;
}

int bufp = 0;
char buf[BUFSIZE];

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
