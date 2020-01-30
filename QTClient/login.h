#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "socket.h"
#include "QtGlobal"
#include "home.h"
#include "registration.h"
#include "QJsonDocument"
#include "QJsonObject"

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
    socket *Client = new socket("127.0.0.2",8888);
    Home *home = new Home();
    Registration *registation = new Registration();
    QJsonObject user;
    void JsonArrivato(const QJsonObject &json);
    const QString login = "login";
    const QString msg = "msg";
    bool connection_granted = false;

signals:
    void give_user(QString);
    void parse_msg(QString, QString);

private slots:
    void manda(QJsonObject msg);
    void on_pushButton_2_clicked();
    void json_received(QJsonObject);
    void OnReadyRead();
};

#endif // MAINWINDOW_H
