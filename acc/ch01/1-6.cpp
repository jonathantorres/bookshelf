// only the first name is stored in the "name" variable
// from the first call to standard input
// and the second name is stored in the "name" variable
// again since it's currently stored in the standard input buffer
#include <iostream>
#include <string>

int main(void)
{
    std::cout << "What is your name? ";
    std::string name;
    std::cin >> name;
    std::cout << "Hello, " << name << std::endl << "And what is yours? ";
    std::cin >> name;
    std::cout << "Hello, " << name << "; nice to meet you too!" << std::endl;
    return 0;
}
