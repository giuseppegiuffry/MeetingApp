#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "socket.h"

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

private:
    Ui::Registration *ui;
    socket *Signin = new socket();
};

#endif // REGISTRATION_H
