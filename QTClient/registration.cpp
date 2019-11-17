#include "registration.h"
#include "ui_registration.h"
#include "QMessageBox"
#include "QDebug"
#include "QJsonDocument"
#include "QJsonObject"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}


void Registration::on_Registra_clicked()
{
    if(ui->Nome->text().isEmpty()==true && ui->Cognome->text().isEmpty()==true && ui->Nick->text().isEmpty()==true && ui->Password->text().isEmpty()==true)
        QMessageBox::about(this,"Warning","Riempire tutti i campi");
    else
    {
        QJsonObject user;
        user.insert("Name",QJsonValue::fromVariant(ui->Nome->text()));
        user.insert("Surname",QJsonValue::fromVariant(ui->Cognome->text()));
        user.insert("Nickname",QJsonValue::fromVariant(ui->Nick->text()));
        user.insert("Password",QJsonValue::fromVariant(ui->Password->text()));
        qDebug() << user;
        Signin->sendJson();//mandare socket con dati registrazione
    }
}
