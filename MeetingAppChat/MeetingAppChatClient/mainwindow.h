#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtSql>
#include <QFileInfo>
#include <chatwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;

    void closeConnection() {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool openConnection() {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/home/giuseppe/Development/QtProjects/MeetingAppChat/database.db");


        if(!mydb.open()) {
            qDebug() << "Failed to open database";
            return false;
        }
        else {
            qDebug() << "Connected to database";
            return true;
        }
    }

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::MainWindow *ui;
    ChatWindow *chatWindow;
};

#endif // MAINWINDOW_H
