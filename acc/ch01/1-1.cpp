// both definitions are valid

#include <iostream>
#include <string>

int main(void)
{
    const std::string hello = "Hello";
    const std::string message = hello + ", world" + "!";

    std::cout << hello << std::endl;
    std::cout << message << std::endl;
    return 0;
}
