/**
 * 3-17.  A Caesar shift (see cryptography) is a very simple class of ciphers for secret messages. Unfortunately, they can be broken using statistical properties of English. Develop a program capable of decrypting Caesar shifts of sufficiently long texts.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char *caesar_encrypt(char *msg)
{
    char *new_msg = NULL;
    int offset = 13;
    int msg_len = strlen(msg);

    new_msg = malloc(msg_len + 1);
    if (!new_msg) {
        return NULL;
    }
    char *new_msg_p = new_msg;

    for (char *msg_p = msg; *msg_p != '\0'; msg_p++) {
        int new_char = *msg_p + offset;
        if (isalpha(*msg_p)) {
            if (new_char > 90 && isupper((int)(*msg_p))) {
                int bounds = new_char - 90;
                new_char = 65 + bounds;
            }
            if (new_char > 122 && islower((int)(*msg_p))) {
                int bounds = new_char - 122;
                new_char = 97 + bounds;
            }
            *new_msg_p = (char)new_char;
        } else {
            *new_msg_p = *msg_p;
        }
        new_msg_p++;
    }
    *new_msg_p = '\0';

    return new_msg;
}

char *caesar_decrypt(char *msg)
{
    char *new_msg = NULL;
    int offset = 13;
    int msg_len = strlen(msg);

    new_msg = malloc(msg_len + 1);
    if (!new_msg) {
        return NULL;
    }

    char *new_msg_p = new_msg;
    for (char *msg_p = msg; *msg_p != '\0'; msg_p++) {
        int new_char = *msg_p - offset;
        if (isalpha(*msg_p)) {
            if (new_char < 65 && isupper((int)(*msg_p))) {
                int bounds = 65 - new_char;
                new_char = 90 - bounds;
            }
            if (new_char < 97 && islower((int)(*msg_p))) {
                int bounds = 97 - new_char;
                new_char = 122 - bounds;
            }
            *new_msg_p = (char)new_char;
        } else {
            *new_msg_p = *msg_p;
        }
        new_msg_p++;
    }
    *new_msg_p = '\0';

    return new_msg;
}

int main(void)
{
    char *name = "Hi, my name is Jonathan Torres";
    char *name_en = caesar_encrypt(name);
    char *name_de = caesar_decrypt(name_en);

    printf("%s\n", name);
    printf("%s\n", name_en);
    printf("%s\n", name_de);

    free(name_en);
    free(name_de);
    return 0;
}
