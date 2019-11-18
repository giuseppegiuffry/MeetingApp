#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>
#include "QJsonDocument"
#include "QJsonObject"
#include "QDataStream"

class socket
{
public:
    socket();
    QTcpSocket *client;
    bool connect(QString indirizzo, quint16 porta);
    void send(QString msg);
    void reg(QJsonObject user);
};

#endif // SOCKET_H
