#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 512
#define BUFSIZE  1024

enum { NAME, PARENS, BRACKETS, ERR };

int gettoken(void);
void dcl(void);
void dirdcl(void);
int getch(void);
void ungetch(int c);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[BUFSIZE];

int main(void)
{
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();

        if (tokentype == ']') {
            printf("syntax error, missing ]\n");
        }

        printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';) {
        ns++;
    }

    dirdcl();

    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

void dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        dcl();

        if (tokentype != ')') {
            printf("error: missing )\n");
            printf("syntax error\n");
            tokentype = ERR;
            return;
        }
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
        printf("syntax error\n");
        tokentype = ERR;
        return;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

int gettoken(void)
{
    int c;
    char *p = token;

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
        for (*p++ = c; (*p++ = getch()) != ']' && (*(p - 1) != '\n');) {
            ;
        }

        *p = '\0';

        if ((*(p - 1)) == ']') {
            return tokentype = BRACKETS;
        } else {
            return tokentype = ']';
        }
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
