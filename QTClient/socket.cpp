#include "socket.h"

socket::socket(QString ind, uint16_t port)
{
    indirizzo = ind;
    porta = port;
}

bool socket::connect(QJsonObject user){
    connectToHost(indirizzo,porta);
    if (waitForConnected(1000)){
        qDebug() << "connesso";
        QDataStream clientstream(this);
        clientstream << QJsonDocument(user).toJson(QJsonDocument::Compact);
        readyRead();
        return true;
      //close();
    }
    else {
        return false;
        qDebug() << "non connesso";
    }
}

void socket::send(QJsonObject msg){
    QDataStream clientstream(this);
    clientstream << QJsonDocument(msg).toJson(QJsonDocument::Compact);
    qDebug() << "dovrei mandare un msg";
}

bool socket::reg(QJsonObject user){
    connectToHost(indirizzo,porta);
    if(waitForConnected())
    {
    qDebug() << "connesso";
    QDataStream clientstream(this);
    clientstream << QJsonDocument(user).toJson(QJsonDocument::Compact);
    qDebug() << "dovrei mandare un Json al server";
    return true;
    }
    else return false;
}
