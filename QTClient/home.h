#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include "QDebug"
#include "QJsonDocument"
#include "QJsonObject"

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private:
    Ui::Home *ui;
    QJsonObject JsonMsg;
    QString nome_mittente;
    QString other_user;
    void closeEvent(QCloseEvent *bar);

public slots:
    void receive_user(QString);
    void receive_msg(QString other_user, QString msg);

private slots:
    void on_sendButton_clicked();

signals:
    void send_msg(QJsonObject);
    void revoke_auth();

};

#endif // HOME_H
