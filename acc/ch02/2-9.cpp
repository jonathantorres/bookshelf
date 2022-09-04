#include <iostream>
#include <string>

int main(void)
{
    int a;
    int b;

    std::cout << "Enter first number: ";
    std::cin >> a;

    if (!a) {
        std::cout << "ERROR: a number must be entered" << std::endl;
        return 1;
    }

    std::cout << "Enter second number: ";
    std::cin >> b;

    if (!b) {
        std::cout << "ERROR: a number must be entered" << std::endl;
        return 1;
    }

    if (a > b) {
        std::cout << "The first number is greater than the second" << std::endl;
    } else if (b > a) {
        std::cout << "The second number is greater than the first" << std::endl;
    } else {
        std::cout << "The numbers are the same" << std::endl;
    }

    return 0;
}

