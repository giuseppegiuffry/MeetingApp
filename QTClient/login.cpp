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
    connect(home,SIGNAL(revoke_auth()),this,SLOT(revoke_auth()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    if(!username.isEmpty() && !password.isEmpty())
    {
        user.insert("login",QJsonValue::fromVariant("login"));
        user.insert("name",QJsonValue::fromVariant(username));
        user.insert("password",QJsonValue::fromVariant(password));
        if(Client->connect(user))
        {
            Client->waitForReadyRead(200);
            if(connection_granted)
            {
                home->setModal(true);
                home->show();
            }
            else
            {
                QMessageBox::critical(this,"Errore","Username e/o password errati!");
                Client->close();
            }
        }
        else QMessageBox::about(this,"Errore","Non Connesso");
        emit(give_user(username));
    }
    else QMessageBox::critical(this,"Errore","Inserire username e/o password!");
}

void MainWindow::on_registerButton_clicked()
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
    qDebug() << "Sono entrato nella readyread";
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
                    qDebug() << "Json letto correttamente";
                    JsonArrivato(jsonDoc.object());
            }
        } else {
            qDebug() << "Sono uscito";
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
                return;
            if (senderVal.isNull() || !senderVal.isString())
                return;
        emit parse_msg(senderVal.toString(),textVal.toString());
    }
    if (json.keys().contains("rematch")){
        emit parse_msg("Sistema","Utente Disconnesso");
    }
}

void MainWindow::revoke_auth()
{
    connection_granted = false;
    Client->close();
    ui->username->clear();
    ui->password->clear();
}

