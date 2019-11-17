#include "socket.h"

socket::socket()
{
    client = new QTcpSocket();
}


bool socket::connect(QString indirizzo, quint16 porta){
    client->connectToHost(indirizzo,porta);
    if (client->waitForConnected(3000)){
        qDebug() << "connesso";
        client->waitForReadyRead(3000);
        qDebug() << "Reading: " <<client->bytesAvailable();
        qDebug() << client->readAll();
        return true;
      //  client->close();
    }
    else {
        return false;
        qDebug() << "non connesso";
    }
}

void socket::send(QString msg){
    QByteArray ba = msg.toLocal8Bit();
    const char *mess = ba.data();
    client->write(mess);
    client->waitForBytesWritten(1000);
}

void socket::sendJson(){
    qDebug() << "implementare sendJson";
}
