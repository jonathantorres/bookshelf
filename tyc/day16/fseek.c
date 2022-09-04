#include <stdlib.h>
#include <stdio.h>

#define MAX 50

int main(void)
{
    FILE *fp;
    int data, count, array[MAX];
    long offset;

    for (count = 0; count < MAX; count++) {
        array[count] = count * 10;
    }

    if ((fp = fopen("random.dat", "wb")) == NULL) {
        fprintf(stderr, "\nError opening file.");
        exit(1);
    }

    if ((fwrite(array, sizeof(int), MAX, fp)) != MAX) {
        fprintf(stderr, "\nError writing data to file.");
        exit(1);
    }

    fclose(fp);

    if ((fp = fopen("random.dat", "rb")) == NULL) {
        fprintf(stderr, "\nError opening file.");
        exit(1);
    }

    while (1) {
        printf("\nEnter element to read, 0-%d, -1 to quit:", MAX-1);
        scanf("%ld", &offset);

        if (offset < 0) {
            break;
        } else if (offset > MAX-1) {
            continue;
        }

        if ((fseek(fp, (offset * sizeof(int)), SEEK_SET)) != 0) {
            fprintf(stderr, "\nError using fseek();");
            exit(1);
        }

        fread(&data, sizeof(int), 1, fp);

        printf("\nElement %ld has value %d", offset, data);
    }

    fclose(fp);

    return 0;
}
