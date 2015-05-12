#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QGraphicsView>
#include <QPicture>
#include <QPainter>
#include <iostream>
#include "quadtree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPicture *pi;
    QPainter *p;
    quadtree<double> *qt;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void updateQTGraph();
    void drawBox(node<double> *tmp,QPainter *p);
    void drawQuadTree(node<double> *tmp,QPainter *p);
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
