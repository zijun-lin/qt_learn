#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fTimer = new QTimer(this);
//    fTimer->start();
    fTimer->stop();
    fTimer->setInterval(1000);
    connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnGetTime_clicked()
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    ui->timeEdit->setTime(curDateTime.time());
    ui->editTime->setText(curDateTime.toString ("hh:mm: ss11"));

    ui->dateEdit->setDate(curDateTime.date());
    ui->editDate->setText(curDateTime.toString("yyyy-MM-dd"));

    ui->dateTimeEdit->setDateTime(curDateTime);
    ui->editDateTime->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void MainWindow::on_timer_timeout()
{
    QTime curTime=QTime::currentTime();
    ui->lcdHour->display(curTime.hour());
    ui->lcdMin->display(curTime.minute());
    ui->lcdSec->display(curTime.second());

    int va = ui->progressBar->value();
    va++;
    if (va>100) {
        va=0;
    }
    ui->progressBar->setValue(va);
}

void MainWindow::on_btnStart_clicked()
{
    fTimer->start();
    fTimeCounter.start();

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnSetIntv->setEnabled(false);
}



void MainWindow::on_btnStop_clicked()
{
    fTimer->stop();
    int tmMsec = fTimeCounter.elapsed();
    int ms = tmMsec % 1000;
    int sec = tmMsec / 1000;

    QString str = QString::asprintf("流逝时间：%d 秒，%d 毫秒", sec, ms);
    ui->LabElapsTime->setText(str);
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnSetIntv->setEnabled(true);
}


