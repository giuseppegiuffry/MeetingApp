#ifndef RCVTHREAD_H
#define RCVTHREAD_H

#include <QObject>
#include "QtCore"
#include "QDebug"
#include "QTcpSocket"
#include "QJsonDocument"
#include "QJsonObject"
#include "home.h"


class RcvThread : public QThread
{
public:
    RcvThread();
    void run(QTcpSocket *client);

public slots:
    void OnReadyRead();

signals:
    void JsonArrivato(QJsonObject);

private:
    QTcpSocket *client;
};

#endif // RCVTHREAD_H
