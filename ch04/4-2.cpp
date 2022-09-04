#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int main(void)
{
    for (int i = 0; i <= 100; i++) {
        std::cout << std::setw(3) << i << std::setw(6) << i*i << std::endl;
    }
    return 0;
}
