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
    Person *p = new(Person);
    Person *p1 = new(Person);
    Person *p2 = new(Person);
    std::cout << p->getAge() << std::endl;
    std::cout << p1->getAge() << std::endl;
    std::cout << p2->getAge() << std::endl;
    std::cout << Person::getTimes() << std::endl;
    delete p;
    delete p1;
    delete p2;
    std::cout << Person::getTimes() << std::endl;
    return 0;
}
