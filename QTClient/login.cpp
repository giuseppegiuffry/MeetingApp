#include "login.h"
#include "ui_login.h"
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
    connect(Client,SIGNAL(readyRead()),this,SLOT(OnReadyRead()));
    connect(this,SIGNAL(parse_msg(QString,QString)),home,SLOT(receive_msg(QString,QString)));
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
        user.insert("login",QJsonValue::fromVariant("login"));
        user.insert("name",QJsonValue::fromVariant(username));
        user.insert("password",QJsonValue::fromVariant(password));
        if(Client->connect(user))
        {
            if(connection_granted)
            {
                home->setModal(true);
                home->show();
            }
            else
            {
                QMessageBox::about(this,"Errore","Dati Errati");
                Client->close();
            }
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

void MainWindow::OnReadyRead()
{
    qDebug() << "sono entrato nella readyread";
    QByteArray jsonData;
    QDataStream socketStream(Client);
    for (;;) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    qDebug() << "json letto correttamente";
                    JsonArrivato(jsonDoc.object());
            }
        } else {
            qDebug() << "Sono Uscito";
            break;
        }
    }
}

void MainWindow::JsonArrivato(const QJsonObject &json)
{
    qDebug() << json;
    if (json.keys().contains("login")){
        connection_granted=true;
    }
    if (json.keys().contains("msg")){
        const QJsonValue textVal = json.value(QLatin1String("msg"));
        const QJsonValue senderVal = json.value(QLatin1String("user_name"));
            if (textVal.isNull() || !textVal.isString())
                return; // the text field was invalid so we ignore
            if (senderVal.isNull() || !senderVal.isString())
                return; // the sender field was invalid so we ignore
        emit parse_msg(senderVal.toString(),textVal.toString());
    }
}

