#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>

class socket
{
public:
    socket();
    QTcpSocket *client;
    bool connect(QString indirizzo, quint16 porta);
    void send(QString msg);
    void sendJson();
};

#endif // SOCKET_H
