#include <iostream>

unsigned long int perimeter(unsigned short int length, unsigned short int width);

int main()
{
    std::cout << perimeter(10, 10) << std::endl;
    return 0;
}

unsigned long int perimeter(unsigned short int length, unsigned short int width)
{
    return (length * 2) + (width * 2);
}
