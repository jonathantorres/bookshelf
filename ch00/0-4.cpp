#include <iostream>
#include <fstream>
#include <string>

int main(void)
{
    std::ifstream fs;
    fs.open("ch00/0-0.cpp", std::ios_base::in);

    if (!fs.is_open()) {
        std::cout << "error opening the file" << std::endl;
        return 1;
    }

    while (true) {
        std::string line;
        if (!std::getline(fs, line, '\n')) {
            break;
        }
        std::cout << line << std::endl;
    }

    fs.close();

    return 0;
}
