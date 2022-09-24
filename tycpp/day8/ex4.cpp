#include <iostream>

int main()
{
    int num;
    int *p_num = &num;
    *p_num = 100;
    std::cout << "num is: " << num << std::endl;
    return 0;
}
