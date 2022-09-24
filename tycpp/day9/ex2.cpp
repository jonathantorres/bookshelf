#include <iostream>

int main()
{
    const int num = 100;
    const int * const p_num = &num;
    num = 200;
    *p_num = 300;
    int num_two;
    p_num = &num_two;
    return 0;
}
