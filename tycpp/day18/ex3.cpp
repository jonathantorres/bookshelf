#include <iostream>

namespace MyStuff {
    class MyClass
    {
    public:
        MyClass() {};
        ~MyClass() {};
        void run() { std::cout << "run!" << std::endl; }
    };
}

int main()
{
    MyStuff::MyClass c;
    c.run();
    return 0;
}
