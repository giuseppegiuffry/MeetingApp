#include "login.h"
#include "ui_mainwindow.h"
#include "QTcpSocket"
#include "QDebug"
#include "socket.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(home,SIGNAL(send_msg(QJsonObject)),this,SLOT(manda(QJsonObject)));
    connect(this,SIGNAL(give_user(QString)),home,SLOT(receive_user(QString)));
    thread.run(Client);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->username->text();
    QString password = ui->username->text();
    if(!username.isEmpty() || !password.isEmpty())
    {
        user.insert("Name",QJsonValue::fromVariant(username));
        user.insert("Password",QJsonValue::fromVariant(password));
        if(Client->connect(user))
        {
        home->setModal(true);
        home->show();
        }
        else QMessageBox::about(this,"Errore","Non Connesso");
        emit(give_user(username));
    }
    else QMessageBox::about(this,"Errore","Inserire Utente e Password!");
}

void MainWindow::on_pushButton_2_clicked()
{
    registation->setModal(true);
    registation->show();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::manda(QJsonObject msg)
{
    Client->send(msg);
}

void MainWindow::json_received(QJsonObject msg)
{
    qDebug() << msg;
}


