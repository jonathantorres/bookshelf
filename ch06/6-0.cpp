#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include <string>

bool space(char c);
bool not_space(char c);
bool is_palindrome(const std::string& s);
std::vector<std::string> split(const std::string& str);

int main(void)
{
    std::string w = "these are a couple of words";
    std::string pal = "madam";
    std::string npal = "Jonathan";
    std::vector<std::string> r = split(w);

    // test the split function
    for (std::vector<std::string>::const_iterator iter = r.begin(); iter != r.end(); iter++) {
        std::cout << "- " << *iter << std::endl;
    }

    // test is palindrome function
    if (is_palindrome(pal)) {
        std::cout << pal << " is a palindrome" << std::endl;
    } else {
        std::cout << pal << " is not a palindrome" << std::endl;
    }

    if (is_palindrome(npal)) {
        std::cout << npal << " is a palindrome" << std::endl;
    } else {
        std::cout << npal << " is not a palindrome" << std::endl;
    }
    return 0;
}

std::vector<std::string> split(const std::string& str)
{
    typedef std::string::const_iterator iter;
    std::vector<std::string> ret;
    iter i = str.begin();

    while (i != str.end()) {
        // ignore leading blanks
        i = std::find_if(i, str.end(), not_space);

        // find end of next word
        iter j = std::find_if(i, str.end(), space);

        // copy the characters in [i, j)
        if (i != str.end()) {
            ret.push_back(std::string(i, j));
        }
        i = j;
    }
    return ret;
}

bool is_palindrome(const std::string& s)
{
    return std::equal(s.begin(), s.end(), s.rbegin());
}

bool space(char c)
{
    return std::isspace(c);
}

bool not_space(char c)
{
    return !std::isspace(c);
}
