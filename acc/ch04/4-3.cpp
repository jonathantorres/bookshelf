#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int main(void)
{
    for (int i = 0; i < 1000; i++) {
        std::cout << std::setw(6) << i << std::setw(10) << i*i << std::endl;
    }
    return 0;
}
