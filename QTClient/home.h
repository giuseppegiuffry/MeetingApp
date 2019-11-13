#ifndef HOME_H
#define HOME_H

#include <QDialog>

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

signals:
    void send_msg(QString);

private:
    Ui::Home *ui;
};

#endif // HOME_H
