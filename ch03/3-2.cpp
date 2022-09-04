#include <iostream>
#include <vector>

int main(void)
{
    // TODO
    std::vector<int> ints = {1,2,3,4,5};

    for (std::vector<int>::size_type i = 0; i < ints.size(); i++) {
        std::cout << ints[i] << std::endl;
    }
    return 0;
}
