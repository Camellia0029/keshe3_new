#include "shape.h"

Shape::Shape(QObject* parent) : QObject(parent)
{
}

Shape::~Shape()
{
}

Circle::Circle(QObject* parent) : Shape(parent)
{
}

int Circle::count() const
{
    // Count the number of circles
    return 0;
}

double Circle::area() const
{
    // Calculate the area of the circle
    return 0.0;
}

double Circle::perimeter() const
{
    // Calculate the perimeter of the circle
    return 0.0;
}

double Circle::length() const
{
    // Calculate the length of the circle
    return 0.0;
}

Rectangle::Rectangle(QObject* parent) : Shape(parent)
{
}

int Rectangle::count() const
{
    // Count the number of rectangles
    return 0;
}

double Rectangle::area() const
{
    // Calculate the area of the rectangle
    return 0.0;
}

double Rectangle::perimeter() const
{
    // Calculate the perimeter of the rectangle
    return 0.0;
}

double Rectangle::length() const
{
    // Calculate the length of the rectangle
    return 0.0;
}
