#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

void Home::on_sendButton_clicked()
{
    QString message = ui->msg->text();
    ui->msg->clear();
    if(message.isEmpty())
        return;
    else{
        JsonMsg.insert("user_name",QJsonValue::fromVariant(nome_mittente));
        JsonMsg.insert("msg",QJsonValue::fromVariant(message));
        emit(send_msg(JsonMsg));

        QListWidgetItem *messageItem = new QListWidgetItem(nome_mittente + ": " + message);
        ui->com->addItem(messageItem);
        messageItem->setTextAlignment(Qt::AlignRight);

        ui->com->scrollToBottom();
    }
}


void Home::receive_user(QString user1){
    nome_mittente = user1;
}

void Home::receive_msg(QString other_user, QString msg){
   this->other_user = other_user;
   QString message = msg;
   message = other_user + ": " + message;
   ui->com->addItem(message);
   ui->com->scrollToBottom();
}

void Home::closeEvent(QCloseEvent *event){
    ui->com->clear();
    emit(revoke_auth());
    QWidget::closeEvent(event);
}
