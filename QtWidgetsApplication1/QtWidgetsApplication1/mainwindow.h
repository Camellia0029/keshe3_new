#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<qmenubar.h>
#pragma execution_character_set("utf-8")
class ShapeAnalyzer;//���η���
class Shape;//����
class Command;//����

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
