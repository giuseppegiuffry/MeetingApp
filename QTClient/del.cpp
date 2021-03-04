#include "del.h"
#include "ui_del.h"

del::del(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::del)
{
    ui->setupUi(this);
    connect(Conferma,SIGNAL(readyRead()),this,SLOT(OnReadyRead()));
}

del::~del()
{
    delete ui;
}

void del::on_confirm_clicked()
{
    if(ui->nickname->text().isEmpty() == true || ui->password->text().isEmpty() || ui->conf_password->text().isEmpty())
        QMessageBox::critical(this,"Errore","Inserisci tutti i campi!");
    else if(ui->password->text() != ui->conf_password->text())
        QMessageBox::critical(this,"Errore","La password non combacia!");
    else {
            user.insert("name",QJsonValue::fromVariant(ui->nickname->text()));
            user.insert("password",QJsonValue::fromVariant(ui->password->text()));
            user.insert("delete",QJsonValue::fromVariant("delete"));
            if(Conferma->reg(user)){
                Conferma->waitForReadyRead(200);
                if(elimination_completed == true)
                {
                    QMessageBox::about(this,"Successo","Eliminazione andata a buon fine");
                    elimination_completed = false;
                    Conferma->close();
                    this->close();
                    ui->nickname->text().clear();
                    ui->password->text().clear();
                    ui->conf_password->text().clear();
                }
                else
                QMessageBox::about(this,"Failed","Eliminazione non completata");
            }
            else
                QMessageBox::about(this,"Errore","Non Connesso");
        }
}

void del::OnReadyRead()
{
    qDebug() << "Sono entrato nella readyread";
    QByteArray jsonData;
    QDataStream socketStream(Conferma);
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

void del::JsonArrivato(const QJsonObject &json)
{
    qDebug() << json;
    if (json.keys().contains("delete")){
        elimination_completed = true;
    }
}
