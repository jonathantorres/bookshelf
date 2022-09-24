#include <iostream>
#include <fstream>
#include <cctype>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cerr << "Need to provide a filename" << std::endl;
        return 1;
    }

    char const *filename = argv[1];
    std::ifstream fin(filename);
    char ch;
    while (fin.get(ch)) {
        if (std::isalpha(ch)) {
            std::cout << ch;
        }
    }
    std::cout << std::endl;
    return 0;
}
