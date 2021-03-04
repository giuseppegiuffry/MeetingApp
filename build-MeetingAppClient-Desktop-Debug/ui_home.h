/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QListWidget *com;
    QLineEdit *msg;
    QPushButton *sendButton;
    QPushButton *pushButton;

    void setupUi(QDialog *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName(QStringLiteral("Home"));
        Home->resize(479, 300);
        com = new QListWidget(Home);
        com->setObjectName(QStringLiteral("com"));
        com->setGeometry(QRect(10, 11, 461, 251));
        msg = new QLineEdit(Home);
        msg->setObjectName(QStringLiteral("msg"));
        msg->setGeometry(QRect(10, 270, 291, 25));
        sendButton = new QPushButton(Home);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(310, 270, 80, 25));
        pushButton = new QPushButton(Home);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 270, 71, 25));

        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QDialog *Home)
    {
        Home->setWindowTitle(QApplication::translate("Home", "Chat Room", Q_NULLPTR));
        sendButton->setText(QApplication::translate("Home", "Invia", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Home", "Rematch", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
