#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void iterate(std::vector<int>& v);

int main(void)
{
    std::vector<int> u(10, 100);
    std::vector<int> v;

    iterate(u);
    iterate(v);
    std::copy(u.begin(), u.end(), std::back_inserter(v));
    iterate(u);
    iterate(v);

    return 0;
}

void iterate(std::vector<int>& v)
{
    std::cout << "size: " << v.size() << std::endl;
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}
