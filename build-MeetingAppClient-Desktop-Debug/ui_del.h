/********************************************************************************
** Form generated from reading UI file 'del.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEL_H
#define UI_DEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_del
{
public:
    QLineEdit *nickname;
    QLineEdit *password;
    QLineEdit *conf_password;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *confirm;

    void setupUi(QDialog *del)
    {
        if (del->objectName().isEmpty())
            del->setObjectName(QStringLiteral("del"));
        del->resize(400, 300);
        nickname = new QLineEdit(del);
        nickname->setObjectName(QStringLiteral("nickname"));
        nickname->setGeometry(QRect(190, 50, 181, 25));
        password = new QLineEdit(del);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(190, 100, 181, 25));
        password->setEchoMode(QLineEdit::Password);
        conf_password = new QLineEdit(del);
        conf_password->setObjectName(QStringLiteral("conf_password"));
        conf_password->setGeometry(QRect(190, 160, 181, 25));
        conf_password->setEchoMode(QLineEdit::Password);
        label = new QLabel(del);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 50, 71, 17));
        label_2 = new QLabel(del);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 100, 81, 17));
        label_3 = new QLabel(del);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 160, 141, 20));
        label_4 = new QLabel(del);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 10, 291, 17));
        confirm = new QPushButton(del);
        confirm->setObjectName(QStringLiteral("confirm"));
        confirm->setGeometry(QRect(140, 210, 89, 25));

        retranslateUi(del);

        QMetaObject::connectSlotsByName(del);
    } // setupUi

    void retranslateUi(QDialog *del)
    {
        del->setWindowTitle(QApplication::translate("del", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("del", "Nickname", Q_NULLPTR));
        label_2->setText(QApplication::translate("del", "Password", Q_NULLPTR));
        label_3->setText(QApplication::translate("del", "Conferma Password", Q_NULLPTR));
        label_4->setText(QApplication::translate("del", "Inserire Nickname e confermare password", Q_NULLPTR));
        confirm->setText(QApplication::translate("del", "Conferma", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class del: public Ui_del {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEL_H
