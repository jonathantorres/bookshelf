#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define MAXLINE 1000 // length of a maximum line to be read
#define NUMBER '0'

int sp = 0;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp = 0;

int getop(char s[], char line[]);
void push(double f);
double pop(void);
int c_getline(char [], int);

int main(void)
{
    int type;
    double op2;
    char s[MAXOP], line[MAXLINE];
    while (c_getline(line, MAXLINE) > 0) {
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
                case '%':
                    op2 = pop();
                    if (op2 != 0) {
                        push(fmod(pop(), op2));
                    }
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break;
                default:
                    printf("error: unknown command %s\n", s);
            }
        }
    }
    return 0;
}

int c_getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while(--lim > 0 && ((c = getchar()) != EOF && c != '\n')) {
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
    if (c == '\0') {
        j = 0;
        return c;
    }
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
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
