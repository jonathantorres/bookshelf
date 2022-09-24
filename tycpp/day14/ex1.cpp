#include <iostream>

class Rocket
{
public:
    Rocket() {};
    ~Rocket() {};
};

class Airplane
{
public:
    Airplane() {};
    ~Airplane() {};
};

class JetPlane: public Rocket, public Airplane
{
public:
    JetPlane() { std::cout << "Jet plane constructor!" << std::endl; };
    ~JetPlane() { };
};

class Seven47: public JetPlane
{
public:
    Seven47() { std::cout << "Seven47 constructor!" << std::endl; };
    ~Seven47() {};
};

int main()
{
    JetPlane jp;
    Seven47 sv;
    return 0;
}
