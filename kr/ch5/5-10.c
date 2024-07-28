#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVAL  1024
#define BUFSIZE 1024
#define MAXOP   1024 // max size of operand or operator
#define NUMBER  '0'  // signal that a number was found

int getop(char s[], char line[]);
void push(double f);
double pop(void);

int pos = 0;

int main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];
    char line[BUFSIZE];

    if (argc != 2) {
        printf("not enough arguments: expr \"numbers operators\"\n");
        exit(1);
    }

    char *expr = argv[1];
    int i;

    for (i = 0; i < (int)(strlen(expr)); i++) {
        line[i] = expr[i];
    }

    line[i++] = '\n';
    line[i]   = '\0';

    while ((type = getop(s, line)) != '\0') {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
        }
    }

    return 0;
}

int getop(char s[], char line[])
{
    int i, c;

    while ((s[0] = c = line[pos++]) == ' ' || c == '\t') {
        ;
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    } else {
        int n = line[pos++];

        line[--pos] = n;

        if (c == '-' && isdigit(n)) {
            c = n;
        } else if (c == '-') {
            return c;
        }
    }

    i = 0;

    if (isdigit(c)) {
        while (isdigit(s[++i] = c = line[pos++])) {
            ;
        }
    }

    if (c == '.') {
        while (isdigit(s[++i] = c = line[pos++])) {
            ;
        }
    }

    s[i] = '\0';

    line[--pos] = c;

    return NUMBER;
}

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
