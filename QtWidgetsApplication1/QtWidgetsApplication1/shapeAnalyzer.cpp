#include "shapeAnalyzer.h"
#include "shape.h"
#include "command.h"

ShapeAnalyzer::ShapeAnalyzer(QObject* parent) : QObject(parent)
{
}

ShapeAnalyzer::~ShapeAnalyzer()
{
    //清空所有几何
    qDeleteAll(m_shapes);
    m_shapes.clear();

    // 清空所有命令
    qDeleteAll(m_commands);
    m_commands.clear();
}

//添加几何
void ShapeAnalyzer::addShape(Shape* shape)
{
    m_shapes.append(shape);
}

//添加命令
void ShapeAnalyzer::addCommand(Command* command)
{
    m_commands.append(command);
}

void ShapeAnalyzer::performAnalysis()
{
    foreach(Command * command, m_commands) {
        command->execute();
    }

    // 对集合进行统计分析
    for (Shape* shape : m_shapes) {
        int count = shape->count();
        double area = shape->area();
        double perimeter = shape->perimeter();
        double length = shape->length();

        //进一步计算和统计结果展示
    }
}
