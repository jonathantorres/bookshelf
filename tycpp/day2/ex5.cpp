#include <iostream>

int add(int a, int b)
{
    std::cout << "In add(), received " << a << " and " << b << std::endl;
    return a + b;
}

int substract(int a, int b)
{
    std::cout << "In substract(), received " << a << " and " << b << std::endl;
    return a - b;
}

int main()
{
    using std::cout;
    using std::cin;

    cout << "I'm in main()!" << std::endl;
    int a, b, c;
    cout << "Enter two numbers: ";
    cin >> a;
    cin >> b;
    cout << "Calling add()!" << std::endl;
    c = add(a, b);
    cout << "Back in main();" << std::endl;
    cout << "c was set to " << c << std::endl;
    cout << "Calling substract()!" << std::endl;
    c = substract(a, b);
    cout << "c was set to " << c << std::endl;
    cout << "Exiting..." << std::endl;
    return 0;
}
