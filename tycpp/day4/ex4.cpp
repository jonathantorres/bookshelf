#include <iostream>

int main()
{
    int a = 2, b = 2, c;
    if ((c = (a - b))) {
        std::cout << "The value of c is: " << c << std::endl;
    }
    return 0;
}
