#pragma once
#ifndef COMMAND_H
#define COMMAND_H
#include <QObject>
#include <algorithm>

//用于基类声明和命令类声明
class Command : public QObject
{
    Q_OBJECT

public:
    explicit Command(QObject* parent = nullptr);
    virtual ~Command();
    virtual void execute() = 0;
};

class ConvexHullCommand : public Command
{
public:
    explicit ConvexHullCommand(QObject* parent = nullptr);

    void execute() override;

private:
    std::vector<QPoint> computeConvexHull(const std::vector<QPoint>& points);
};

class BufferCommand : public Command
{
public:
    explicit BufferCommand(QObject* parent = nullptr);
    void execute() override;
};

class OverlayCommand : public Command
{
public:
    explicit OverlayCommand(QObject* parent = nullptr);
    void execute() override;
};

class DelaunayCommand : public Command
{
public:
    explicit DelaunayCommand(QObject* parent = nullptr);
    void execute() override;
};

class PerimeterCommand : public Command
{
public:
    explicit PerimeterCommand(QObject* parent = nullptr);
    void execute() override;
};

class AreaCommand : public Command
{
public:
    explicit AreaCommand(QObject* parent = nullptr);
    void execute() override;
};

class CountCommand : public Command
{
public:
    explicit CountCommand(QObject* parent = nullptr);
    void execute() override;
};
#endif // COMMAND_H
