#include <iostream>
#include <string>

int main(void)
{
    std::string shortest;
    std::string longest;
    std::string word;

    while (std::cin >> word) {
        if (
            (shortest != "" && word.size() < shortest.size())
            || shortest == ""
        ) {
            shortest = word;
        }

        if (
            (longest != "" && word.size() > longest.size())
            || longest == ""
        ) {
            longest = word;
        }
    }

    std::cout << "Shortest word: " << shortest << " (" << shortest.size() << ")" << std::endl;
    std::cout << "Longest word: " << longest << " (" << longest.size() << ")" << std::endl;

    return 0;
}
