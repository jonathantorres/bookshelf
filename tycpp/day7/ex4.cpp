#include <iostream>

int main()
{
    int i = 100;
    do {
        std::cout << i << std::endl;
        i += 2;
    } while (i <= 200);
    return 0;
}
