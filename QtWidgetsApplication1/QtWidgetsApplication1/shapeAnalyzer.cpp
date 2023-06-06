#include "shapeAnalyzer.h"
#include "shape.h"
#include "command.h"

ShapeAnalyzer::ShapeAnalyzer(QObject* parent) : QObject(parent)
{
}

ShapeAnalyzer::~ShapeAnalyzer()
{
    //������м���
    qDeleteAll(m_shapes);
    m_shapes.clear();

    // �����������
    qDeleteAll(m_commands);
    m_commands.clear();
}

//��Ӽ���
void ShapeAnalyzer::addShape(Shape* shape)
{
    m_shapes.append(shape);
}

//�������
void ShapeAnalyzer::addCommand(Command* command)
{
    m_commands.append(command);
}

void ShapeAnalyzer::performAnalysis()
{
    foreach(Command * command, m_commands) {
        command->execute();
    }

    // �Լ��Ͻ���ͳ�Ʒ���
    for (Shape* shape : m_shapes) {
        int count = shape->count();
        double area = shape->area();
        double perimeter = shape->perimeter();
        double length = shape->length();

        //��һ�������ͳ�ƽ��չʾ
    }
}
