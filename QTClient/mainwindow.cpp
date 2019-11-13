#include "mainwindow.h"
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
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_pushButton_clicked()
{
    if(Client->connect("127.0.0.2",8888)){
        home->show();
        connect(home,SIGNAL(send_msg(QString)),this,SLOT(manda(QString)));
    }
    else QMessageBox::about(this,"Errore","Non Connesso");

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::manda(QString msg){
    Client->send(msg);
}
