#include <iostream>

int power_up(unsigned int num, unsigned short int power);

int main()
{
    int num, pow;
    int result;
    std::cout << "Enter a number and a power:" << std::endl;
    std::cout << "number: ";
    std::cin >> num;
    std::cout << "power: ";
    std::cin >> pow;
    result = power_up(num, pow);
    std::cout << "Result is: " << result << std::endl;
    return 0;
}

int power_up(unsigned int num, unsigned short int power)
{
    if (power == 1) {
        return num;
    }
    return (num * power_up(num, power - 1));
}
