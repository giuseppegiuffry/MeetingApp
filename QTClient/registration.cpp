#include "registration.h"
#include "ui_registration.h"
#include "QMessageBox"
#include "QDebug"


Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    connect(Signin,SIGNAL(readyRead()),this,SLOT(OnReadyRead()));
}

Registration::~Registration()
{
    delete ui;
}


void Registration::on_registratiButton_clicked()
{
    if(ui->Nome->text().isEmpty()==true || ui->Cognome->text().isEmpty()==true ||
            ui->Nick->text().isEmpty()==true || ui->Password->text().isEmpty()==true ||
            ui->Bio->toPlainText().isEmpty()==true)
        QMessageBox::critical(this,"Errore","Inserisci tutti i campi!");
    else if(ui->Bio->toPlainText().length() < 50){
        QMessageBox::critical(this,"Errore","Inserisci almeno 50 caratteri nella biografia");
    }
    else
    {
        getInfo();
        qDebug() << user;
        if(Signin->reg(user)){
            Signin->waitForReadyRead(200);
            if(registration_completed == true){
                QMessageBox::about(this,"Successo","Registrazione andata a buon fine");
                registration_completed = false;
                Signin->close();
                this->close();
                ui->Nome->text().clear();
                ui->Cognome->text().clear();
                ui->Nick->text().clear();
                ui->Password->text().clear();
                ui->Bio->toPlainText().clear();
                }
            else
                QMessageBox::about(this,"Failed","Registrazione non completata");
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


void Registration::OnReadyRead()
{
    qDebug() << "Sono entrato nella readyread";
    QByteArray jsonData;
    QDataStream socketStream(Signin);
    for (;;) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    qDebug() << "Json letto correttamente";
                    JsonArrivato(jsonDoc.object());
            }
        } else {
            qDebug() << "Sono uscito";
            break;
        }
    }
}

void Registration::JsonArrivato(const QJsonObject &json)
{
    qDebug() << json;
    if (json.keys().contains("bio")){
        registration_completed = true;
    }
}
