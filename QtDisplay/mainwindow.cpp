#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->rBtnBlue,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(ui->rBtnRed,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(ui->rBtnBlack,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    ShowChat();


}

void MainWindow::ShowChat()
{
    // generate some data
    QVector<double> x(101), y(101);
    for (int i = 0; i < 101; ++i) {
        x[i] = i / 50.0 - 1;
        y[i] = x[i] * x[i];
    }
    // create graph and assign data to it
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels
    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");
    // set axes ranges, so we see all data
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chkBoxUnder_clicked(bool checked)
{
    QFont font=ui->txtEdit->font();
    font.setUnderline(checked);
    ui->txtEdit->setFont(font);
}

void MainWindow::on_chkBoxItalic_clicked(bool checked)
{
    QFont font=ui->txtEdit->font();
    font.setItalic(checked);
    ui->txtEdit->setFont(font);
}

void MainWindow::on_chkBoxBold_clicked(bool checked)
{
    QFont font=ui->txtEdit->font();
    font.setBold(checked);
    ui->txtEdit->setFont(font);
}

void MainWindow::setTextFontColor()
{
    QPalette plet=ui->txtEdit->palette();
    if (ui->rBtnBlue->isChecked())
        plet.setColor(QPalette::Text,Qt::blue);
    else if (ui->rBtnRed->isChecked())
       plet.setColor(QPalette::Text,Qt::red);
    else if (ui->rBtnBlack->isChecked())
        plet.setColor(QPalette::Text,Qt::black);
    else
       plet.setColor(QPalette::Text,Qt::black);

    ui->txtEdit->setPalette(plet);
}

void MainWindow::on_btnOK_clicked()
{
    if (!auto_on_) {
        auto_on_ = true;
        ui->btnOK->setText("OKK");
    } else {
        auto_on_ = false;
        ui->btnOK->setText("Not OKK");
    }
}
