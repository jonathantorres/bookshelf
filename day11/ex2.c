#include <stdio.h>

struct data {
    int amount;
    float price;
    float shipping_price;
};

struct data *p_info;

int main(int argc, char const *argv[])
{
    struct data info;
    p_info = &info;
    info.amount = 100;
    p_info->price = 50.99;
    // (*p_info).price = 50.99;

    return 0;
}
