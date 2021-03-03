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

private:
    Ui::MainWindow *ui;
    socket *Client = new socket("127.0.0.2",8888);
    Home *home = new Home();
    Registration *registation = new Registration();
    QJsonObject user;
    QJsonObject hello;
    void JsonArrivato(const QJsonObject &json);
    const QString login = "login";
    const QString msg = "msg";
    bool connection_granted = false;

signals:
    void give_user(QString);
    void parse_msg(QString, QString);

private slots:
    void manda(QJsonObject msg);
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_actionExit_triggered();
    void json_received(QJsonObject);
    void OnReadyRead();
    void revoke_auth();
};

#endif // MAINWINDOW_H
