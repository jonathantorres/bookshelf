#include <stdio.h>

struct data {
    float amount;
    char fname[30];
    char lname[30];
} rec;

int main(int argc, char const *argv[])
{
    printf("Enter the donor's first and last names, \n");
    printf("separated by a space: ");
    scanf("%s %s", rec.fname, rec.lname);

    printf("\nEnter the donation amount: ");
    scanf("%f", &rec.amount);

    printf("\nDonor %s %s gave $%.2f\n", rec.fname, rec.lname, rec.amount);

    return 0;
}
