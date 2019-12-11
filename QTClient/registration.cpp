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
    if(ui->Nome->text().isEmpty()==true || ui->Cognome->text().isEmpty()==true ||
            ui->Nick->text().isEmpty()==true || ui->Password->text().isEmpty()==true ||
            ui->Bio->toPlainText().isEmpty()==true)
        QMessageBox::critical(this,"Errore","Inserisci tutti i campi!");
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
    user.insert("name",QJsonValue::fromVariant(ui->Nome->text()));
    user.insert("surname",QJsonValue::fromVariant(ui->Cognome->text()));
    user.insert("nickname",QJsonValue::fromVariant(ui->Nick->text()));
    user.insert("password",QJsonValue::fromVariant(ui->Password->text()));
    user.insert("sex",QJsonValue::fromVariant(ui->Sesso->currentText()));
    user.insert("interested",QJsonValue::fromVariant(ui->Interesse->currentText()));
    user.insert("bio",QJsonValue::fromVariant(ui->Bio->toPlainText()));
}
