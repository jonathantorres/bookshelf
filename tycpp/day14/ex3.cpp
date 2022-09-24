#include <iostream>

class Vehicle
{
public:
    Vehicle() {};
    ~Vehicle() {};
    virtual void start() = 0;
    virtual void brake() = 0;
};

class Car: public Vehicle
{
public:
    Car() {};
    ~Car() {};
    virtual void start() = 0;
    void brake() { std::cout << "Car brakes!" << std::endl; }
};

class Bus: public Vehicle
{
public:
    Bus() {};
    ~Bus() {};
    void start() { std::cout << "Bus starts!" << std::endl; }
    void brake() { std::cout << "Bus brakes!" << std::endl; }
};

class SportsCar: public Car
{
public:
    SportsCar() {};
    ~SportsCar() {};
    void start() { std::cout << "SportsCar starts!" << std::endl; }
};

class Coupe: public Car
{
public:
    Coupe() {};
    ~Coupe() {};
    void start() { std::cout << "Coupe starts!" << std::endl; }
};

int main()
{
    Coupe c;
    c.start();
    c.brake();
    Bus b;
    b.start();
    b.brake();
    return 0;
}
