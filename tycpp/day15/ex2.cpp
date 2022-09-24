#include <iostream>

class Person
{
public:
    Person() { this->age = 11; Person::times++; };
    ~Person() { Person::times--; };
    int getAge();
    static char first_name[];
    static int times;

private:
    int age;
};

int Person::getAge()
{
    return this->age;
}

int Person::times = 0;
char Person::first_name[] = "Jonathan";

int main()
{
    Person *p = new(Person);
    Person *p1 = new(Person);
    Person *p2 = new(Person);
    std::cout << p->getAge() << std::endl;
    std::cout << p1->getAge() << std::endl;
    std::cout << p2->getAge() << std::endl;
    std::cout << Person::times << std::endl;
    delete p;
    delete p1;
    delete p2;
    std::cout << Person::times << std::endl;
    return 0;
}
