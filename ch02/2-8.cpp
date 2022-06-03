#include <iostream>

int main(void)
{
    int p = 1;
    for (int i = 1; i <= 10; i++) {
        p *= i;
    }
    std::cout << p << std::endl;
    return 0;
}
