#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "socket.h"
#include "QtGlobal"
#include "home.h"
#include "registration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    socket *Client = new socket();
    Home *home = new Home();
    Registration *registation = new Registration();
signals:

private slots:
    void manda(QString);
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
