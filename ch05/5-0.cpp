#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::max;

string::size_type width(const vector<string>& v);
vector<string> frame(const vector<string>& v);

int main(void)
{
    vector<string> s = {"one", "two", "three", "four"};
    vector<string> f = frame(s);
    vector<string>::const_iterator iter = f.begin();

    while (iter != f.end()) {
        std::cout << *iter << std::endl;
        iter++;
    }
    return 0;
}

string::size_type width(const vector<string>& v)
{
    string::size_type maxlen = 0;
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        maxlen = max(maxlen, v[i].size());
    }
    return maxlen;
}

vector<string> frame(const vector<string>& v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    // write the top border
    ret.push_back(border);

    // write each interior row, bordered by an asterisk and a space
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
    }

    // write the bottom border
    ret.push_back(border);

    return ret;
}
