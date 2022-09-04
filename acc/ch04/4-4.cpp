#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ios>

int main(void)
{
    for (double i = 0; i <= 100; i++) {
        double s = i*i;
        std::cout << std::fixed << std::setprecision(2) << std::setw(8)
            << i << std::setw(10) << s << std::endl;
    }
    return 0;
}
