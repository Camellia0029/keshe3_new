#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<qmenubar.h>
#pragma execution_character_set("utf-8")
class ShapeAnalyzer;//几何分析
class Shape;//几何
class Command;//命令

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_analyzeButton_clicked();

private:
    Ui::MainWindow* ui;
    ShapeAnalyzer* m_shapeAnalyzer;
    Shape* m_shape;
    Command* m_command;
};

#endif // MAINWINDOW_H
