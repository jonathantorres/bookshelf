#include <iostream>

int divide(unsigned short int a, unsigned short int b);

int main()
{
    int a, b;
    int result;
    std::cout << "Enter two numbers:" << std::endl;
    std::cout << "a: ";
    std::cin >> a;
    std::cout << "b: ";
    std::cin >> b;
    result = divide(a, b);
    if (result == -1) {
        std::cout << "Cannot divide by zero" << std::endl;
    } else {
        std::cout << "Result is: " << result << std::endl;
    }
    return 0;
}

int divide(unsigned short int a, unsigned short int b)
{
    if (b == 0) {
        return -1;
    } else {
        return a / b;
    }
}
