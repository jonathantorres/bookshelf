#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encode_character(int ch, int val);
int decode_character(int ch, int val);

int main(int argc, char const *argv[])
{
    FILE *fh;
    int rv = 1;
    int ch = 0;
    unsigned int ctr = 0;
    int val = 5;
    char buffer[257];

    if (argc != 3) {
        printf("\nError: Wrong number of parameters...");
        printf("\n\nUsage:\n %s filename action", argv[0]);
        printf("\n\nWhere:");
        printf("\nfilename = name of file to code or decode");
        printf("\naction = D for decode or C for encode\n\n");
        rv = -1;
    } else {
        if ((argv[2][0] == 'D') || (argv[2][0] == 'd')) {
            fh = fopen(argv[1], "r");
            if (fh <= 0) {
                printf("\n\nError opening file...");
                rv = -2;
            } else {
                ch = getc(fh);
                while (!feof(fh)) {
                    ch = decode_character(ch, val);
                    putchar(ch);
                    ch = getc(fh);
                }
                fclose(fh);
                printf("\n\nFile decoded to screen.\n");
            }
        } else {
            fh = fopen(argv[1], "w");
            if (fh <= 0) {
                printf("\n\nError creating file...");
                rv = -3;
            } else {
                printf("\n\nEnter text to be coded.");
                printf("Enter a blank line to end.\n\n");

                while (gets(buffer) != NULL) {
                    if (buffer[0] == 0) {
                        break;
                    }

                    for (ctr = 0; ctr < strlen(buffer); ctr++) {
                        ch = encode_character(buffer[ctr], val);
                        ch = fputc(ch, fh);
                    }
                }
                printf("\n\nFile encoded to file.\n");
                fclose(fh);
            }
        }
    }

    return (rv);
}

int encode_character(int ch, int val)
{
    ch = ch + val;
    return (ch);
}

int decode_character(int ch, int val)
{
    ch = ch - val;
    return (ch);
}



