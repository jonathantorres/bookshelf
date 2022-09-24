#include <iostream>

class Person
{
public:
    Person() { this->age = 11; Person::times++; };
    ~Person() { Person::times--; };
    int getAge();
    static int getTimes();
    static char first_name[];

private:
    int age;
    static int times;
};

int Person::getAge()
{
    std::cout << "calling getAge()" << std::endl;
    return this->age;
}

int Person::getTimes()
{
    return Person::times;
}

int Person::times = 0;
char Person::first_name[] = "Jonathan";

int main()
{
    int (Person::*getter)();
    getter = Person::getAge;

    Person p;
    (p.*getter)();
    return 0;
}
