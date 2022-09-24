#include <iostream>

int main()
{
    char full_name[255];
    std::cout << "Enter your full name: ";
    std::cin.getline(full_name, 255);
    std::cout << full_name << std::endl;
    return 0;
}
