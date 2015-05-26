#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pi = new QPicture();
    p = new QPainter(pi);
    qt = new quadtree<double>(1,0,500,500,0);

    p->setRenderHint(QPainter::Antialiasing);
    p->setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::SquareCap));

    qt->insert(std::pair<double,double>(10.0, 15.0), 6.6);
    qt->insert(std::pair<double,double>(150.0, 240.0), 5.5);
    qt->insert(std::pair<double,double>(100.0, 100.0), 4.4);
    qt->insert(std::pair<double,double>(60.0, 60.0), 3.3);
    qt->insert(std::pair<double,double>(430.0, 430.0), 3.3);
    qt->insert(std::pair<double,double>(380.0, 60.0), 3.3);
    qt->insert(std::pair<double,double>(380.0, 70.0), 3.3);
    qt->insert(std::pair<double,double>(90.0, 372.0), 3.3);
    qt->insert(std::pair<double,double>(60.0, 120.0), 3.3);

    std::vector<std::pair<std::pair<double,double>,double> > result;
    result = qt->searchRange(std::pair<double,double>(0,500),std::pair<double,double>(500,0));

    for(int i = 0;i<result.size();i++)
    {
        p->drawPoint(result[i].first.first,result[i].first.second);
    }

    node<double> *tmp = qt->getRoot();
    drawQuadTree(tmp,p);
    p->end(); // Don't forget this line!

    ui->qtgraph->setPicture(*pi);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBox(node<double> *tmp,QPainter *p)
{
    p->drawLine(tmp->x.first, tmp->y.first, tmp->x.second, tmp->y.first);
    p->drawLine(tmp->x.first, tmp->y.first, tmp->x.first, tmp->y.second);
    p->drawLine(tmp->x.second, tmp->y.second, tmp->x.second, tmp->y.first);
    p->drawLine(tmp->x.first, tmp->y.second,tmp->x.second,tmp->y.second);
}

void MainWindow::drawQuadTree(node<double> *tmp,QPainter *p)
{
    if(tmp->first == nullptr)
    {
        drawBox(tmp,p);
        return;
    } else {
        drawQuadTree(tmp->first,p);
        drawQuadTree(tmp->second,p);
        drawQuadTree(tmp->third,p);
        drawQuadTree(tmp->fourth,p);
    }
}

void MainWindow::on_pushButton_clicked()
{
    qt->insert(std::pair<double,double>(ui->lineEdit->text().toDouble(),
                                        ui->lineEdit_2->text().toDouble()),
               ui->lineEdit->text().toDouble());

    updateQTGraph();
}

void MainWindow::updateQTGraph()
{
    QPicture *piold = pi;
    QPainter *pold = p;
    pi = new QPicture();
    p = new QPainter(pi);

    p->setRenderHint(QPainter::Antialiasing);
    p->setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::SquareCap));

    std::vector<std::pair<std::pair<double,double>,double> > result;
    result = qt->searchRange(std::pair<double,double>(0,500),std::pair<double,double>(500,0));

    for(int i = 0;i<result.size();i++)
    {
        p->drawPoint(result[i].first.first,result[i].first.second);
    }

    node<double> *tmp = qt->getRoot();
    drawQuadTree(tmp,p);
    p->end(); // Don't forget this line!

    ui->qtgraph->setPicture(*pi);

    delete piold;
    delete pold;
}

void MainWindow::on_pushButton_2_clicked()
{
    qt->deleteKey(std::pair<double,double>(ui->lineEdit->text().toDouble(),ui->lineEdit_2->text().toDouble()));
    updateQTGraph();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget->clear();

    std::vector<std::pair<std::pair<double,double>,double> > result;
    result = qt->searchRange(std::pair<double,double>(ui->lineEdit_3->text().toDouble(),ui->lineEdit_4->text().toDouble()),
                             std::pair<double,double>(ui->lineEdit_5->text().toDouble(),ui->lineEdit_6->text().toDouble()));

    for(int i = 0;i<result.size();i++)
    {
        ui->listWidget->addItem("X:"+QString::number(result[i].first.first) + " Y:" + QString::number(result[i].first.second));
    }
}
