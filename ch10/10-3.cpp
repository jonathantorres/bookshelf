#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>

template <class T, class It>
double median(It begin, It end);

int main(void)
{
    std::vector<double> v = { 11, 23, 43, 45, 52, 52, 33 };
    double m = median<double>(v.begin(), v.end());

    double x[] = { 11, 23, 43, 45, 52, 52, 33 };
    double n = median<double>(x, x+7);

    std::cout << m << std::endl;
    std::cout << n << std::endl;
    return 0;
}

template <class T, class It>
double median(It begin, It end)
{
    if (begin == end) {
        throw std::domain_error("median of an empty container");
    }

    std::vector<T> tmp;
    for (It i = begin; i != end; i++) {
        tmp.push_back(*i);
    }

    typedef typename std::vector<T>::size_type tmp_size;
    tmp_size size = tmp.size();

    std::sort(tmp.begin(), tmp.end());
    tmp_size mid = size / 2;

    return size % 2 == 0 ? (tmp[mid] + tmp[mid-1]) / 2 : tmp[mid];
}
