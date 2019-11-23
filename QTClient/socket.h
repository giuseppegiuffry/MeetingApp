#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>
#include "QJsonDocument"
#include "QJsonObject"
#include "QDataStream"

class socket : public QTcpSocket
{
public:
    socket(QString ind, uint16_t port);
    bool connect(QJsonObject user);
    void send(QJsonObject msg);
    bool reg(QJsonObject user);

private:
    QString indirizzo;
    uint16_t porta;
};

#endif // SOCKET_H
