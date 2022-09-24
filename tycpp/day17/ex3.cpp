#include <iostream>

int main()
{
    char ch;
    std::cout << "enter a phrase: ";
    while (std::cin.get(ch) != 0) {
        if (ch == '!')
           std::cin.putback('$');
        else
           std::cout << ch;
        while (std::cin.peek() == '#')
           std::cin.ignore(1,'#');
    }
    return 0;
}
