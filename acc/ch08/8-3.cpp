#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <iterator>

using std::string;
using std::vector;
using std::cout;
using std::cout;
using std::cin;
using std::endl;
using std::domain_error;

template<class T, class Rit>
T median(Rit b, Rit e);

int main(void)
{
    vector<int> v = {100, 40, 50, 11, 2, 30, 44, 70 };
    int m = median<int>(v.begin(), v.end());
    cout << "median: " << m << endl;

    return 0;
}

template<class T, class Rit>
T median(Rit b, Rit e)
{
    typedef typename std::iterator_traits<Rit>::difference_type diff_type;
    diff_type d = std::distance(b, e);

    if (d <= 0) {
        throw domain_error("median of an empty vector");
    }

    std::sort(b, e);

    diff_type mid = d/2;
    diff_type n = 0;

    for (; n < mid; n++, b++) {
        // nothing to do, just moving the iterator b
    }

    if (d % 2 == 0) {
        return (*b + *--b) / 2;
    }

    return *b;
}
