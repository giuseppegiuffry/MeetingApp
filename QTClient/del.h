#ifndef DEL_H
#define DEL_H

#include <QDialog>
#include "socket.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QMessageBox"

namespace Ui {
class del;
}

class del : public QDialog
{
    Q_OBJECT

public:
    explicit del(QWidget *parent = 0);
    ~del();

private slots:
    void on_confirm_clicked();
    void OnReadyRead();

private:
    Ui::del *ui;
    void JsonArrivato(const QJsonObject &json);
    socket *Conferma = new socket("127.0.0.2",8888);
    QJsonObject user;
    bool elimination_completed = false;
};

#endif // DEL_H
