#include "mainwindow.h"
#include "mywidget.h"

#include<QWidget>
#include<QLayout>
#include<QPainter>
#include<QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1280,720);
    setCentralWidget(new MyWidget(this));
    auto layout = new QHBoxLayout();
    setLayout(layout);
    show();
}

MainWindow::~MainWindow()
{
}

