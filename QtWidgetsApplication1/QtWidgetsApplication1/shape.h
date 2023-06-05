#pragma once
#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include <QObject>
//几何图形类声明和具体图形实现
class Shape : public QObject
{
    Q_OBJECT
public:
    explicit Shape(QObject* parent = nullptr);
    virtual ~Shape();

    virtual int count() const = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual double length() const = 0;
};

class Circle : public Shape
{
public:
    explicit Circle(QObject* parent = nullptr);
    int count() const override;
    double area() const override;
    double perimeter() const override;
    double length() const override;
};

class Rectangle : public Shape
{
public:
    explicit Rectangle(QObject* parent = nullptr);
    int count() const override;
    double area() const override;
    double perimeter() const override;
    double length() const override;
};


#endif // SHAPE_H

