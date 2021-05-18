#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ShowChat();


private slots:
    void on_chkBoxUnder_clicked(bool checked);

    void on_chkBoxItalic_clicked(bool checked);

    void on_chkBoxBold_clicked(bool checked);

    void setTextFontColor();

    void on_btnOK_clicked();

private:
    Ui::MainWindow *ui;
    int auto_on_ = false;
};

#endif // MAINWINDOW_H
