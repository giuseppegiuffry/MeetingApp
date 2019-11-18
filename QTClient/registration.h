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
    void on_Registra_clicked();
    void getInfo();

private:
    Ui::Registration *ui;
    socket *Signin = new socket();
    QJsonObject user;
};

#endif // REGISTRATION_H
