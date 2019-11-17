#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <mainwindow.h>

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
    void on_pushButton_signup_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
