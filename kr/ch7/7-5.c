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
void ungetch(int c);

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

int getop(char s[])
{
    int rc;
    char c;
    float f;

    while ((rc = scanf("%c", &c)) != EOF) {
        if ((s[0] = c) != ' ' && c != '\t') {
            break;
        }
    }

    s[1] = '\0';

    if (rc == EOF) {
        return EOF;
    } else if (!isdigit(c) && c != '.') {
        return c;
    }

    ungetc(c, stdin);
    scanf("%f", &f);
    sprintf(s, "%f", f);

    return NUMBER;
}

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
