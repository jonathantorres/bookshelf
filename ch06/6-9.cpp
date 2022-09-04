#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string s;

void add_to_s(const std::string& i);

int main(void)
{
    std::vector<std::string> words = {"one", "two", "three", "four"};

    std::cout << s << std::endl;

    std::for_each(words.begin(), words.end(), add_to_s);

    std::cout << s << std::endl;

    return 0;
}

void add_to_s(const std::string& i)
{
    s.append(i);
    s.append(1, ' ');
}
