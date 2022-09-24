#include <iostream>

class String
{
public:
    String() { std::cout << "String init." << std::endl; };
    ~String() {};
};

class Animal
{
public:
    Animal() { std::cout << "Animal init." << std::endl; };
    ~Animal() {};
private:
    String name;
};

int main()
{
    Animal a;
    return 0;
}
