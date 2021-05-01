#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "display.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCustomPlot *customPlot = new QCustomPlot(this);
    DisplayCheck(customPlot);


}

MainWindow::~MainWindow() {
    delete ui;
}

