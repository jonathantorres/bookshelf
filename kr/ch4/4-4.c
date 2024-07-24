#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL    1024
#define BUFSIZE   1024
#define MAXOP     1024 // max size of operand or operator
#define NUMBER    '0'  // signal that a number was found
#define PRINT     'p'
#define DUPLICATE 'd'
#define SWAP      's'
#define CLEAR     'c'

void printtop(void);
double top(void);
void duptop(void);
void swaptop(void);
void clear(void);

int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);

int main(void)
{
    int type, op;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                op = 0;
                push(atof(s));
                break;
            case PRINT:
                op = 0;
                printtop();
                break;
            case DUPLICATE:
                op = 0;
                duptop();
                break;
            case SWAP:
                op = 0;
                swaptop();
                break;
            case CLEAR:
                op = 0;
                clear();
                break;
            case '+':
                op = 1;
                push(pop() + pop());
                break;
            case '*':
                op = 1;
                push(pop() * pop());
                break;
            case '-':
                op  = 1;
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op  = 1;
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                op  = 1;
                op2 = pop();
                if (op2 != 0) {
                    push((int)pop() % (int)op2);
                }
                break;
            case '\n':
                if (op) {
                    printf("\t%.8g\n", pop());
                }
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

void printtop(void)
{
    printf("%f\n", top());
}

void duptop(void)
{
    double t = top();
    push(t);
}

void swaptop(void)
{
    double a = pop();
    double b = pop();

    push(a);
    push(b);
}

void clear(void)
{
    sp = 0;
}

double top(void)
{
    return val[sp];
}

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

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    } else {
        int n = getch();

        ungetch(n);

        if (c == '-' && isdigit(n)) {
            c = n;
        } else if (c == '-') {
            return c;
        }
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
        ungetch(c);
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
