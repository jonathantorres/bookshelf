#include <iostream>

class Shape
{
    public:
        Shape();
        ~Shape();
};

Shape::Shape() { }
Shape::~Shape() { }

class Rectangle: public Shape
{
    public:
        Rectangle(int length, int width);
        ~Rectangle();
};

Rectangle::Rectangle(int length, int width): Shape()
{
    //
}
Rectangle::~Rectangle() { }

class Square: public Rectangle
{
    public:
        Square(int length);
        ~Square();
};

Square::Square(int length): Rectangle(length, length)
{
    //
}
Square::~Square() { }

int main()
{
    Square sq(100);
    return 0;
}
