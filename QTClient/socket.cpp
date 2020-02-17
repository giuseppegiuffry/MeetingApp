#include "socket.h"

socket::socket(QString ind, uint16_t port)
{
    indirizzo = ind;
    porta = port;
}

bool socket::connect(QJsonObject user){
    connectToHost(indirizzo,porta);
    if (waitForConnected(1000)){
        qDebug() << "Connesso";
        QDataStream clientstream(this);
        clientstream << QJsonDocument(user).toJson(QJsonDocument::Compact);
        return true;
      //close();
    }
    else {
        return false;
        qDebug() << "Non connesso";
    }
}

void socket::send(QJsonObject msg){
    QDataStream clientstream(this);
    clientstream << QJsonDocument(msg).toJson(QJsonDocument::Compact);
    qDebug() << "Dovrei mandare un msg";
}

bool socket::reg(QJsonObject user){
    connectToHost(indirizzo,porta);
    if(waitForConnected())
    {
    qDebug() << "Connesso";
    QDataStream clientstream(this);
    clientstream << QJsonDocument(user).toJson(QJsonDocument::Compact);
    qDebug() << "Dovrei mandare un Json al server";
    return true;
    }
    else return false;
}
