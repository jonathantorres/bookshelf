// no, the program is not correct
// the variable "x" is not defined on the scope that is used
#include <iostream>
#include <string>

int main(void)
{
    { std::string s = "a string";
    { std::string x = s + ", really";
    std::cout << s << std::endl;
    std::cout << x << std::endl;
    }
    }
    return 0;
}

// this version is wrong
// int main(void)
// {
//     { std::string s = "a string";
//     { std::string x = s + ", really";
//     std::cout << s << std::endl; }
//     std::cout << x << std::endl;
//     }
//     return 0;
// }
