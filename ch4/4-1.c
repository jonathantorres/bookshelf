#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);
int strindex(char s[], char t[]);
void reverse(char s[], int len);

int main(void)
{
    char msg[] = "banana";
    char sub[] = "na";
    printf("%d\n", strrindex(msg, sub));
    return 0;
}

int strrindex(char s[], char t[])
{
    int slen = (int)strlen(s);
    int tlen = (int)strlen(t);

    reverse(s, slen);
    reverse(t, tlen);
    int i = strindex(s, t);
    if (i >= 0) {
        i = (slen-tlen) - i;
    }
    reverse(s, slen);
    reverse(t, tlen);
    return i;
}

int strindex(char s[], char t[])
{
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
            ;
        }
        if (k > 0 && t[k] == '\0') {
            return i;
        }
    }
    return -1;
}

void reverse(char s[], int len)
{
    int c, i, j;
    for (i = 0, j = len-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
