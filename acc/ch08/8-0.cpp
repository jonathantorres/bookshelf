#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <iterator>

using std::string;
using std::vector;
using std::cout;
using std::cout;
using std::cin;
using std::endl;
using std::domain_error;

template <class Out>
void split(const string& str, Out os);

template<class T>
T median(vector<T> v);

bool space(char c);
bool not_space(char c);

int main(void)
{
    string s;
    vector<string> lines;

    while (std::getline(cin, s)) {
        lines.push_back(s);
    }

    for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); it++) {
        split(*it, std::ostream_iterator<string>(cout, " "));
    }
    cout << endl;

    vector<int> v = {100, 40, 50, 11, 2, 30, 44, 70 };
    int m = median(v);
    cout << "median: " << m << endl;

    return 0;
}

template <class Out>
void split(const string& str, Out os)
{
    typedef string::const_iterator iter;
    iter i = str.begin();

    while (i != str.end()) {
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);

        // find end of next word
        iter j = find_if(i, str.end(), space);

        // copy the characters in [i, j)
        if (i != str.end()) {
            *os++ = string(i, j);
        }
        i = j;
    }
}

template<class T>
T median(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;
    vec_sz size = v.size();

    if (size == 0) {
        throw domain_error("median of an empty vector");
    }

    sort(v.begin(), v.end());
    vec_sz mid = size/2;

    return size % 2 == 0 ? (v[mid] + v[mid-1]) / 2 : v[mid];
}

bool space(char c)
{
    return std::isspace(c);
}

bool not_space(char c)
{
    return !std::isspace(c);
}
