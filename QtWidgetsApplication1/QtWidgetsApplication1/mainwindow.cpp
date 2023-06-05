#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapeAnalyzer.h"
#include "shape.h"
#include "command.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_shapeAnalyzer = new ShapeAnalyzer(this);
    m_shape = new Circle(this); // ʹ�����м�������
    m_command = new ConvexHullCommand(this); // ʹ��������������
    m_shapeAnalyzer->addShape(m_shape);
    m_shapeAnalyzer->addCommand(m_command);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_analyzeButton_clicked()
{
    m_shapeAnalyzer->performAnalysis();
}
