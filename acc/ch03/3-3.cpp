#include <iostream>
#include <map>

int main(void)
{
    std::map<std::string, int> m;
    std::string word;

    std::cout << "Enter the words: ";
    while (std::cin >> word) {
        m[word]++;
    }

    for (const auto &n: m) {
        std::cout << n.second << ": " << n.first << std::endl;
    }
    return 0;
}
