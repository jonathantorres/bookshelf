#include <iostream>

int main()
{
    unsigned short int your_age;
    unsigned short int *p_your_age = &your_age;
    *p_your_age = 50;
    std::cout << "age is: " << your_age << std::endl;
    return 0;
}
