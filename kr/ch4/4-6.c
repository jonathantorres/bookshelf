#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL   1024
#define BUFSIZE  1024
#define MAXOP    1024 // max size of operand or operator
#define NUMBER   '0'  // signal that a number wes found
#define VARIABLE 'x'  // name of the variable for the latest printed value

int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);

double x;

int main(void)
{
    int type, var = 0;
    double op2, v;
    char s[MAXOP];
    double vars[26];

    for (int i = 0; i < 26; i++) {
        vars[i] = 0.0;
    }

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case VARIABLE:
                push(x);
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
            case '=':
                pop();
                if (var >= 'a' && var <= 'z') {
                    vars[var - 'a'] = pop();
                } else {
                    printf("error: no variable name\n");
                }
                break;
            case '\n':
                v = pop();
                printf("\t%.8g\n", v);
                break;
            default:
                if (type >= 'a' && type <= 'z') {
                    push(vars[type - 'a']);
                } else if (type == 'v') {
                    push(x);
                } else {
                    printf("error: unknown command %s\n", s);
                }
        }

        var = type;
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
