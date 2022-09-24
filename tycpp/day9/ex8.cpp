#include <iostream>

class Cat
{
public:
    Cat(int age) { this->age = age; };
    ~Cat() {};
    int getAge() const { return this->age; };
private:
    int age;
};

Cat *makeCat(int age);

int main()
{
    int age = 7;
    Cat *boots = makeCat(age);
    std::cout << "boots is " << boots->getAge() << " years old" << std::endl;
    delete boots;
    boots = 0;
    return 0;
}

Cat *makeCat(int age)
{
    Cat *p_cat = new Cat(age);
    return p_cat;
}
