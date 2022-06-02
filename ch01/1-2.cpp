// the first definition is valid
// the second one is not, since it's concatenating two
// literal strings together

#include <iostream>
#include <string>

int main(void)
{
    const std::string exclam = "!";
    const std::string message = "Hello" + ", world" + exclam;

    std::cout << exclam << std::endl;
    std::cout << message << std::endl;
}
