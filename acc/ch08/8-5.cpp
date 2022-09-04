#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <cctype>

using std::string;
using std::vector;
using std::map;
using std::istream;
using std::cout;
using std::cin;
using std::endl;

bool space(char c);
bool not_space(char c);
std::vector<std::string> split(const std::string& str);

template <class It>
void xref(istream& in, It ret, vector<string> find_words(const string& str));

int main(void)
{
    // call xref using split by default
    map<string, vector<int>> ret;
    xref(cin, std::inserter(ret, ret.begin()), split);

    // write the results
    for (map<string, vector<int>>::const_iterator it = ret.begin(); it != ret.end(); ++it) {
        // write the word
        cout << it->first << " occurs on line(s): ";

        // followed by one or more line numbers
        vector<int>::const_iterator line_it = it->second.begin();
        cout << *line_it; //write the first line number
        ++line_it;

        // write the rest of the line numbers, if any
        while (line_it != it->second.end()) {
            cout << ", " << *line_it;
            ++line_it;
        }

        cout << endl;
    }
    return 0;
}

// find all the lines that refer to each word in the input
template <class It>
void xref(istream& in, It ret, vector<string> find_words(const string& str))
{
    string line;
    int line_number = 0;
    map<string, vector<int>> m;

    // read the next line
    while (getline(in, line)) {
        ++line_number;

        // break the input line into words
        vector<string> words = find_words(line);

        // remember that each word occurs on the current line
        for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
            m[*it].push_back(line_number);
        }
    }
    copy(m.begin(), m.end(), ret);
}

vector<string> split(const string& str)
{
    typedef string::const_iterator iter;
    vector<string> ret;
    iter i = str.begin();

    while (i != str.end()) {
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);

        // find end of next word
        iter j = find_if(i, str.end(), space);

        // copy the characters in [i, j)
        if (i != str.end()) {
            ret.push_back(string(i, j));
        }
        i = j;
    }
    return ret;
}

bool space(char c)
{
    return std::isspace(c);
}

bool not_space(char c)
{
    return !std::isspace(c);
}
