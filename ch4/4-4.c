#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXVAL 100
#define BUFSIZE 100
#define MAXOP 100     // max size of operand or operator
#define NUMBER '0'    // signal that a number was found
#define PRINT 'p'     // print the element without poping
#define DUPLICATE 'd' // duplicate element
#define SWAP 's'      // swap the top two elements
#define CLEAR 'c'     // clear the stack
#define VARIABLE 'x'  // name of the variable for the latest printed value

int sp = 0;
double val[MAXVAL];
double x;

char buf[BUFSIZE];
int bufp = 0;

int getop(char s[]);
void push(double f);
double pop(void);
void peek(void);
void dup(void);
void swap(void);
void clear(void);
int getch(void);
void ungetch(int c);

int main(void)
{
    int type, operator;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                operator = 1;
                push(atof(s));
                break;
            case VARIABLE:
                operator = 1;
                push(x);
                break;
            case '+':
                operator = 1;
                push(pop() + pop());
                break;
            case '*':
                operator = 1;
                push(pop() * pop());
                break;
            case '-':
                operator = 1;
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                operator = 1;
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                operator = 1;
                op2 = pop();
                if (op2 != 0) {
                    push(fmod(pop(), op2));
                }
                break;
            case PRINT:
                operator = 0;
                peek();
                break;
            case DUPLICATE:
                operator = 0;
                dup();
                break;
            case SWAP:
                operator = 0;
                swap();
                break;
            case CLEAR:
                operator = 0;
                clear();
                break;
            case '\n':
                if (operator) {
                  x = pop();
                  printf("\t%.8g\n", x);
                }
                break;
            default:
                printf("error: unknown command %s\n", s);
        }
    }
    return 0;
}

/* peek: prints without poping */
void peek(void)
{
    x = val[sp-1];
    printf("%g\n", x);
}

/* duplicate: duplicates the last element */
void dup(void)
{
    push(val[sp]);
}

/* swap: swaps the top 2 elements */
void swap()
{
    double temp = val[sp-2];
    val[sp-2] = val[sp-1];
    val[sp-1] = temp;
}

/* clear: clears the stack */
void clear(void)
{
    sp = 0;
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
