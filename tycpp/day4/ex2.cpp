#include <iostream>

int main()
{
    int a, b, c;
    std::cout << "Please enter 3 numbers: " << std::endl;
    std::cout << "a: ";
    std::cin >> a;
    std::cout << std::endl << "b: ";
    std::cin >> b;
    std::cout << std::endl << "c: ";
    std::cin >> c;
    std::cout << std::endl;

    if (c == (a - b)) {
        std::cout << "a: " << a << " minus b: " << b << " equals c:" << c << std::endl;
    } else {
        std::cout << "a - b does not equal c" << std::endl;
    }
    return 0;
}
