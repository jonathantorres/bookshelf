#include <iostream>
#include <algorithm>
#include <vector>

template<class Bi>
void my_reverse(Bi begin, Bi end);

template<class T>
void my_swap(T a, T b);

void print(int n);

int main(void)
{
    std::vector<int> n = { 1, 2, 3, 4, 5 };
    std::for_each(n.begin(), n.end(), print);
    std::cout << std::endl;

    reverse(n.begin(), n.end());
    std::for_each(n.begin(), n.end(), print);
    std::cout << std::endl;

    return 0;
}

template<class Bi>
void my_reverse(Bi begin, Bi end)
{
    while (begin != end) {
        --end;

        if (begin != end) {
            my_swap(*begin++, *end);
        }
    }
}

template<class T>
void my_swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

void print(int n)
{
    std::cout << n << " ";
}
