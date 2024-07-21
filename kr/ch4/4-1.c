#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);

int main(void)
{
    printf("%d\n", strrindex("banana", "na"));
    printf("%d\n", strrindex("Jonathan", "an"));
    printf("%d\n", strrindex("Jonathan", "nat"));
    printf("%d\n", strrindex("foo", "bar"));

    return 0;
}

int strrindex(char s[], char t[])
{
    int i, j, k;

    for (i = strlen(s) - 1; i >= 0; --i) {
        for (j = i, k = strlen(t) - 1; k >= 0 && s[j] == t[k]; --j, --k) {
            ;
        }

        if (k == -1) {
            return j + 1;
        }
    }

    return -1;
}
