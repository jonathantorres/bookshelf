#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL  1024
#define BUFSIZE 1024
#define MAXOP   1024 // max size of operand or operator
#define NUMBER  '0'  // signal that a number was found

int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
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
            case '%':
                op2 = pop();
                if (op2 != 0) {
                    push((int)pop() % (int)op2);
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
        }
    }
    return 0;
}

int sp = 0;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

int getop(char s[])
{
    int i, c;
    static int p = 0;

    if (p == 0) {
        c = getch();
    } else {
        c = p;
        p = 0;
    }

    while ((s[0] = c) == ' ' || c == '\t') {
        c = getch();
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }

    i = 0;

    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }

    if (c == '.') {
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }

    s[i] = '\0';
    if (c != EOF) {
        p = c;
    }

    return NUMBER;
}

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
