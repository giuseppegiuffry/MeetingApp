#include "registration.h"
#include "ui_registration.h"
#include "QMessageBox"
#include "QDebug"


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
    if(ui->Nome->text().isEmpty()==true || ui->Cognome->text().isEmpty()==true || ui->Nick->text().isEmpty()==true || ui->Password->text().isEmpty()==true)
        QMessageBox::about(this,"Warning","Riempire tutti i campi");
    else
    {
        getInfo();
        qDebug() << user;
        if(Signin->reg(user)){
            qDebug() << user;
            Signin->waitForReadyRead(100);
            //implementare ifelse per comunicare se la registrazione è andata a buon fine oppure no
            Signin->close();
            this->close();
        }
        else
            QMessageBox::about(this,"Errore","Non Connesso");
    }
}

void Registration::getInfo()
{
    user.insert("Name",QJsonValue::fromVariant(ui->Nome->text()));
    user.insert("Surname",QJsonValue::fromVariant(ui->Cognome->text()));
    user.insert("Nickname",QJsonValue::fromVariant(ui->Nick->text()));
    user.insert("Password",QJsonValue::fromVariant(ui->Password->text()));
    user.insert("Sex",QJsonValue::fromVariant(ui->Sesso->currentText()));
    user.insert("Interested",QJsonValue::fromVariant(ui->Interesse->currentText()));
    user.insert("Bio",QJsonValue::fromVariant(ui->Bio->toPlainText()));
}
