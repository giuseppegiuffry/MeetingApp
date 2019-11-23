#include "rcvthread.h"

RcvThread::RcvThread()
{

}


void RcvThread::run(QTcpSocket *client)
{
    qDebug() << "Running";
    this->client = client;
    connect(this->client,&QTcpSocket::readyRead,this,&RcvThread::OnReadyRead);
}


void RcvThread::OnReadyRead()
{
    qDebug() << "sono entrato nella readyread";
    QByteArray jsonData;
    QDataStream socketStream(client);
    for (;;) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    qDebug() << "json letto correttamente";
                    emit(JsonArrivato(jsonDoc.object()));
            }
        } else {
            break;
        }
    }
}

void RcvThread::JsonArrivato(QJsonObject)
{
    qDebug() << "mandoJson";
}
