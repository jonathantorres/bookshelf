#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXVAL 100
#define BUFSIZE 100
#define MAXLINE 1000  // length of a maximum line to be read
#define MAXOP 100     // max size of operand or operator
#define NUMBER '0'    // signal that a number wes found
#define PRINT 'p'     // print the element witout poping
#define DUPLICATE 'd' // duplicate element
#define SWAP 's'      // swap the top two elements
#define CLEAR 'c'     // clear the stack
#define VARIABLE 'x'  // name of the variable for the latest printed value
#define NAME 'n'      // name of the mathematical operation

int sp = 0;
double val[MAXVAL];
double x;

char buf[BUFSIZE];
int bufp = 0;

int get_line(char s[], int len);
int getop(char s[], char line[]);
void push(double f);
double pop(void);
void peek(void);
void dup(void);
void swap(void);
void clear(void);
void mathfunc(char s[]);

int main(void)
{
    int type, operator;
    double op2;
    char s[MAXOP], line[MAXLINE];

    while (get_line(line, MAXLINE) > 0) {
        while ((type = getop(s, line)) != '\0') {
            switch (type) {
                case NUMBER:
                    operator = 1;
                    push(atof(s));
                    break;
                case NAME:
                    operator = 1;
                    mathfunc(s);
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
    }

    return 0;
}

void mathfunc(char s[])
{
    double op2;
    if (strcmp(s, "sin") == 0) {
        push(sin(pop()));
    } else if (strcmp(s, "cos") == 0) {
        push(cos(pop()));
    } else if (strcmp(s, "exp") == 0) {
        push(exp(pop()));
    } else if (strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    } else {
        printf("error: %s not supported\n", s);
    }
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

int get_line(char s[], int len)
{
    int c, i;
    i = 0;
    while(--len > 0 && ((c = getchar()) != EOF && c != '\n')) {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';

    return i;
}

int j = 0;
int getop(char s[], char line[])
{
    int i, c;
    if (line[j] == '\n') {
        j++;
        return '\n';
    }
    while (((s[0] = c = line[j++]) != '\0') && (((c == ' ') || (c == '\t')))) {
        //
    }
    s[1] = '\0';
    i = 0;
    if (islower(c)) {
        while (islower(s[++i] = c = line[j++])) {
            //
        }
        s[i] = '\0';
        if (strlen(s) > 1) {
            return NAME;
        }
        return c;
    }
    if (c == '\0') {
        j = 0;
        return c;
    }
    if (!isdigit(c) && c != '.') {
        return c;
    }
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = line[j++])) {
            //
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = line[j++])) {

        }
    }
    s[i] = '\0';

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
