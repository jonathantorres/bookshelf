#include <iostream>

class Person
{
public:
    Person() { this->age = 11; Person::times++; };
    ~Person() { Person::times--; };
    static char first_name[];
    static int times;

private:
    int age;
};

int Person::times = 0;
char Person::first_name[] = "Jonathan";

int main()
{
    return 0;
}
