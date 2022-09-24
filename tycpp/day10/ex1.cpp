#include <iostream>

class SimpleCircle
{
public:
    SimpleCircle();
    SimpleCircle(int radius);
    ~SimpleCircle();
    int getRadius();
    void setRadius(int radius);
    const SimpleCircle *operator++();
    const SimpleCircle operator++(int val);
private:
    int *radius;
};

SimpleCircle::SimpleCircle()
{
    this->radius = new int;
    *this->radius = 5;
}

SimpleCircle::SimpleCircle(int radius)
{
    this->setRadius(radius);
}

SimpleCircle::~SimpleCircle()
{
    delete this->radius;
}

void SimpleCircle::setRadius(int radius)
{
    this->radius = new int;
    *this->radius = radius;
}

int SimpleCircle::getRadius()
{
    return *this->radius;
}

const SimpleCircle *SimpleCircle::operator++()
{
    ++(*this->radius);
    return this;
}

const SimpleCircle SimpleCircle::operator++(int)
{
    SimpleCircle tmp(*this);
    ++(*this->radius);
    return tmp;
}

int main()
{
    SimpleCircle *cir = new SimpleCircle(10);
    std::cout << "radius: " << cir->getRadius() << std::endl;
    ++(*cir);
    std::cout << "radius: " << cir->getRadius() << std::endl;
    (*cir)++;
    std::cout << "radius: " << cir->getRadius() << std::endl;
    return 0;
}
