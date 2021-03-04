/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QPushButton *registratiButton;
    QTextEdit *Bio;
    QLabel *label_7;
    QLineEdit *Nome;
    QLabel *label_2;
    QLineEdit *Cognome;
    QLabel *label_3;
    QLineEdit *Nick;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *Sesso;
    QComboBox *Interesse;
    QLabel *label;
    QLineEdit *Password;

    void setupUi(QDialog *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QStringLiteral("Registration"));
        Registration->resize(492, 403);
        registratiButton = new QPushButton(Registration);
        registratiButton->setObjectName(QStringLiteral("registratiButton"));
        registratiButton->setGeometry(QRect(200, 360, 89, 25));
        Bio = new QTextEdit(Registration);
        Bio->setObjectName(QStringLiteral("Bio"));
        Bio->setGeometry(QRect(120, 250, 361, 99));
        label_7 = new QLabel(Registration);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 270, 111, 31));
        Nome = new QLineEdit(Registration);
        Nome->setObjectName(QStringLiteral("Nome"));
        Nome->setGeometry(QRect(120, 10, 361, 25));
        label_2 = new QLabel(Registration);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 66, 17));
        Cognome = new QLineEdit(Registration);
        Cognome->setObjectName(QStringLiteral("Cognome"));
        Cognome->setGeometry(QRect(120, 50, 361, 25));
        label_3 = new QLabel(Registration);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 68, 17));
        Nick = new QLineEdit(Registration);
        Nick->setObjectName(QStringLiteral("Nick"));
        Nick->setGeometry(QRect(120, 90, 361, 25));
        label_4 = new QLabel(Registration);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(11, 131, 65, 17));
        label_5 = new QLabel(Registration);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 170, 39, 17));
        label_6 = new QLabel(Registration);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 210, 89, 17));
        Sesso = new QComboBox(Registration);
        Sesso->setObjectName(QStringLiteral("Sesso"));
        Sesso->setGeometry(QRect(120, 170, 361, 25));
        Interesse = new QComboBox(Registration);
        Interesse->setObjectName(QStringLiteral("Interesse"));
        Interesse->setGeometry(QRect(120, 210, 361, 25));
        label = new QLabel(Registration);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 42, 17));
        Password = new QLineEdit(Registration);
        Password->setObjectName(QStringLiteral("Password"));
        Password->setGeometry(QRect(120, 130, 361, 25));
        Password->setEchoMode(QLineEdit::Password);

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QDialog *Registration)
    {
        Registration->setWindowTitle(QApplication::translate("Registration", "Registrazione", Q_NULLPTR));
        registratiButton->setText(QApplication::translate("Registration", "Registrati", Q_NULLPTR));
        label_7->setText(QApplication::translate("Registration", "Raccontaci di te", Q_NULLPTR));
        label_2->setText(QApplication::translate("Registration", "Cognome", Q_NULLPTR));
        label_3->setText(QApplication::translate("Registration", "Nickname", Q_NULLPTR));
        label_4->setText(QApplication::translate("Registration", "Password", Q_NULLPTR));
        label_5->setText(QApplication::translate("Registration", "Sesso", Q_NULLPTR));
        label_6->setText(QApplication::translate("Registration", "Interessato a", Q_NULLPTR));
        Sesso->clear();
        Sesso->insertItems(0, QStringList()
         << QApplication::translate("Registration", "Uomo", Q_NULLPTR)
         << QApplication::translate("Registration", "Donna", Q_NULLPTR)
        );
        Interesse->clear();
        Interesse->insertItems(0, QStringList()
         << QApplication::translate("Registration", "Donna", Q_NULLPTR)
         << QApplication::translate("Registration", "Uomo", Q_NULLPTR)
        );
        Interesse->setCurrentText(QApplication::translate("Registration", "Donna", Q_NULLPTR));
        label->setText(QApplication::translate("Registration", "Nome", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
