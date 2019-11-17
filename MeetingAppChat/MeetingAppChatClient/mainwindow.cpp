#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chatWindow = new ChatWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username, password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();

    if(!openConnection()) {
        qDebug()<<"Failed to open the database";
        return;
    }

    openConnection();

    QSqlQuery query;

    query.prepare("select * from account where username='"+username+"' and password='"+password+"'");

    if(query.exec()) {
        int count = 0;

        while(query.next()) {
            count++;
        }
        if(count == 1) {
            ui->label->setText("Username e password corretti");
            // closeConnection();
            // this->hide();
            chatWindow->show();
        }
        if(count < 1) {
            ui->label->setText("Username e/o password errati");
            QMessageBox::critical(this, tr("Error"), tr("Username e/o password errati"));
        }

    }

}


void MainWindow::on_pushButton_register_clicked()
{
    Registration registerWindow;
    registerWindow.setModal(true);
    registerWindow.exec();
}
