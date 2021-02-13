#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "socket.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QMessageBox"

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();

private slots:
    void on_registratiButton_clicked();
    void getInfo();
    void OnReadyRead();

private:
    Ui::Registration *ui;
    socket *Signin = new socket("127.0.0.1",8888);
    QJsonObject user;
    void JsonArrivato(const QJsonObject &json);
    bool registration_completed = false;
};

#endif // REGISTRATION_H
