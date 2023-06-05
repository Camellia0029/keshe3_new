#pragma once
#ifndef SHAPEANALYZER_H
#define SHAPEANALYZER_H
#include <QObject>
#include <QList>
//用于图形分析器类声明
class Shape;
class Command;

class ShapeAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit ShapeAnalyzer(QObject* parent = nullptr);
    ~ShapeAnalyzer();

    void addShape(Shape* shape);
    void addCommand(Command* command);
    void performAnalysis();

private:
    QList<Shape*> m_shapes;
    QList<Command*> m_commands;
};

#endif // SHAPEANALYZER_H

