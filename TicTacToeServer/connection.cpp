#include "connection.h"
#include <QTcpSocket>
#include "reply.h"
#include "requests/testrequest.h"
#include "requests/unknownrequest.h"
#include "requestfactory.h"

Connection::Connection(QTcpSocket *client, QObject *parent) : QObject(parent)
{
    m_client = client;
    connect(m_client, &QTcpSocket::readyRead,
            this,     &Connection::onReadyRead);

    connect(m_client, &QTcpSocket::disconnected,
            this,     &Connection::deleteLater);
}

Connection::~Connection()
{
    delete m_client;
    m_client = nullptr;
}

void Connection::onReadyRead()
{
    QByteArray data = m_client->readAll();
    std::shared_ptr<Request> request = RequestFactory::createRequest(data, this);
    emit requestReady(request);
}

void Connection::onReplyReady(const Reply & /*reply*/)
{

}


