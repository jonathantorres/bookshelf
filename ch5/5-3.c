#include <stdio.h>

void p_strcat(char *s, char *t);
void n_strcat(char s[], char t[]);

int main(void)
{
    char name[100] = "Jonathan ";
    char *last_name = "Torres";
    p_strcat(name, last_name);
    printf("%s\n", name);
    return 0;
}

void p_strcat(char *s, char *t)
{
    // find end of s
    while (*s != '\0') {
        s++;
    }
    while ((*s = *t) != '\0') {
        // copy t
        s++;
        t++;
    }
}

void n_strcat(char s[], char t[])
{
    int i = 0, j = 0;
    while (s[i] != '\0') {
        i++;
        // find end of s
    }
    while ((s[i++] = t[j++]) != '\0') {
        // copy t
    }
}
