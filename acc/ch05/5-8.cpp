#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::max;

string::size_type width(const vector<string>& v);
vector<string> frame(const vector<string>& v);
vector<string> hcat(const vector<string>& left, const vector<string>& right);

int main(void)
{
    vector<string> l = {"one", "two", "three", "four"};
    vector<string> r = {"one-l", "two-l", "three-l", "four-l"};
    vector<string> h = hcat(l, r);
    vector<string>::const_iterator iter = h.begin();

    while (iter != h.end()) {
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

vector<string> hcat(const vector<string>& left, const vector<string>& right)
{
    vector<string> ret;

    // add 1 to leave a space between pictures
    string::size_type width1 = width(left) + 1;
    // indices to look at elements from left and right respectively
    vector<string>::size_type i = 0, j = 0;

    // continue until we've seen all rows from both pictures
    while (i != left.size() || j != right.size()) {
        // construct new string to hold characters from both pictures
        string s;
        // copy a row from the left-hand side, if there is one
        if (i != left.size()) {
            s = left[i++];
        }

        // pad to full width
        s += string(width1 - s.size(), ' ');

        // copy a row from the right-hand side, if there is one
        if (j != right.size()) {
            s += right[j++];
        }

        // add s to the picture we're creating
        ret.push_back(s);
    }

    return ret;
}
