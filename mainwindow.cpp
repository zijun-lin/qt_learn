#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCustomPlot *customPlot = new QCustomPlot(this);
    customPlot->resize(600, 600); // set picture size

    setupQuadraticDemo(customPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot) {
    demoName = "Quadratic Demo";
    QVector<double> x(101), y(101);
    for (int i=0; i<101; ++i) {
      x[i] = i/50.0 - 1;
      y[i] = x[i]*x[i];
    }
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
}
