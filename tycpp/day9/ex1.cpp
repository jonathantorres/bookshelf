#include <iostream>

int main()
{
    int num = 100;
    int &r_num = num;
    int *p_num = &num;

    std::cout << "num is: " << num << std::endl;
    r_num = 200;
    std::cout << "num is: " << num << std::endl;
    *p_num = 300;
    std::cout << "num is: " << num << std::endl;
    return 0;
}
