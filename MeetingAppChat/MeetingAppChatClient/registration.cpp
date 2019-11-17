#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    MainWindow conn;

    if(!conn.openConnection())
        ui->label_conn_status->setText("Failed to open database");
    else
        ui->label_conn_status->setText("Connected to database");
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_signup_clicked()
{
    MainWindow conn;

    QString name, surname, username, password, country, sex, biography;
    qint32 age;
    name = ui->text_name->text();
    surname = ui->text_surname->text();
    username = ui->text_username->text();
    password = ui->text_password->text();
    country = ui->text_country->text();
    sex = ui->comboBox_sex->currentText();
    age = ui->spinBox_age->value();
    biography = ui->text_biography->toPlainText();

    if(name.isEmpty() || surname.isEmpty() || username.isEmpty() || password.isEmpty() ||
            country.isEmpty() || biography.isEmpty()) {
        QMessageBox::critical(this, tr("Errore"), tr("Inserisci tutti i campi!"));
    } else {

        if(!conn.openConnection()) {
            qDebug()<<"Failed to open the database";
            return;
        }

        conn.openConnection();

        QSqlQuery query, query2;

        query.prepare("insert into users(name, surname, country, age, sex, biography) values(:name, :surname, :country, :age, :sex, :biography)");
        query2.prepare("insert into account(username, password) values(:username, :password)");

        query.bindValue(":name", name);
        query.bindValue(":surname", surname);
        query.bindValue(":country", country);
        query.bindValue(":age", age);
        query.bindValue(":sex", sex);
        query.bindValue(":biography", biography);

        query2.bindValue(":username", username);
        query2.bindValue(":password", password);


        if(query.exec() && query2.exec()) {
            QMessageBox::information(this, tr("Messaggio"), tr("Utente registrato"));
            query.finish();
            query2.finish();
            conn.closeConnection();
        }
        else {
            QMessageBox::critical(this, tr("Error::"), query.lastError().text());
        }
    }





}
