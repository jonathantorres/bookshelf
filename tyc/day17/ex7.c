#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *strstri(const char* str, const char* substr);

int main(void)
{
    char full_name[] = "Jonathan Torres";
    char search[] = "j";
    char *loc;

    // loc = strstr(full_name, search);
    loc = strstri(full_name, search);

    printf("Target: %s\n", full_name);

    if (loc == NULL) {
        puts("Target was not found.");
    } else {
        printf("%s was found in location %zu\n", search, loc - full_name);
    }

    return 0;
}

char *strstri(const char* str, const char* substr)
{
    char new_str[80], new_substr[80];
    char *location;

    for (int i = 0; i < strlen(str); i++) {
        if (isalpha(str[i])) {
            new_str[i] = tolower(str[i]);
        } else {
            new_str[i] = str[i];
        }
    }
    new_str[strlen(str)] = '\0';

    for (int j = 0; j < strlen(substr); j++) {
        if (isalpha(substr[j])) {
            new_substr[j] = tolower(substr[j]);
        } else {
            new_substr[j] = substr[j];
        }
    }
    new_substr[strlen(substr)] = '\0';

    location = strstr(new_str, new_substr);

    if (location != NULL) {
        return &str[location - new_str];
    } else {
        return location;
    }
}
