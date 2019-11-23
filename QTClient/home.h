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
    QString nome_mittente;

public slots:
    void receive_user(QString);

private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

signals:
    void send_msg(QJsonObject);

private:
    Ui::Home *ui;
    QJsonObject JsonMsg;
};

#endif // HOME_H
