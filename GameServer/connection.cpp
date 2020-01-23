#include "connection.h"

Connection::Connection(QTcpSocket *client, QObject *parent)
{
    m_client = client;
    connect(m_client, &QTcpSocket::readyRead,
            this,     &Connection::onReadyRead);

    connect(m_client, &QTcpSocket::disconnected,
            this,     &Connection::deleteLater);
}

void Connection::onReadyRead()
{
    QByteArray requestData = m_client->readAll();
    emit onRequestReady(requestData);
}

void Connection::onReplyReady(const QByteArray &reply)
{
    m_client->write(reply, reply.size());
}
