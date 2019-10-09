#include "connection.h"

Connection::Connection(QTcpSocket *client, QObject *parent) : QObject(parent)
{
    m_client = client;
    connect(m_client, &QTcpSocket::readyRead,
            this,   &Connection::onReadyRead);

    connect(m_client, &QTcpSocket::disconnected,
            this,   &Connection::deleteLater);
}

Connection::~Connection()
{
    delete m_client;
    m_client = nullptr;
}

void Connection::onReadyRead()
{
    sender();
}
