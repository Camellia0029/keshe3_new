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

   // m_shapeAnalyzer = new ShapeAnalyzer(this);
    //m_shape = new Circle(this); // 使用已有几何类型
    //m_command = new ConvexHullCommand(this); // 使用已有命令类型
    //m_shapeAnalyzer->addShape(m_shape);
    //m_shapeAnalyzer->addCommand(m_command);

    QMenuBar* bar = menuBar();//创建菜单栏
    setMenuBar(bar);
    //创建菜单
    QMenu* geoMenu = bar->addMenu("几何分析");
    QMenu* staMenu = bar->addMenu("统计分析");
    //创建菜单项
    geoMenu->addAction("凸包计算");
    //添加分割线
    geoMenu->addSeparator();
    geoMenu->addAction("叠加求并");
    //创建菜单项
    staMenu->addAction("周长统计");
    //添加分割线
    staMenu->addSeparator();
    staMenu->addAction("面积统计");
    //添加分割线
    staMenu->addSeparator();
    staMenu->addAction("个数统计");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_analyzeButton_clicked()
{
    m_shapeAnalyzer->performAnalysis();
}
