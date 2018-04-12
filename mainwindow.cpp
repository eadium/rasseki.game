#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MapField::mouseReleaseEvent(QMouseEvent *e) {
    qDebug() << "Mouse event worked";
    QPoint point = e->pos();
    ui->heroInfo->append("TEST");

    qDebug() << point.x() << " and " << point.y();
}

/*
    qDebug() << "x = " << w.x();
    qDebug() << "y = " << w.y();
    qDebug() << "height = " << w.height();
    qDebug() << "width = " << w.width();
    QPoint pos = w.mapToGlobal(QPoint(0,0));
    qDebug() << "x = " << pos.rx();
    qDebug() << "y = " << pos.ry();
    qDebug() << "x = " << pos.x();
    qDebug() << "y = " << pos.y();
*/
