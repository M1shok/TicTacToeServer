#include "gameserver.h"

GameServer::GameServer(quint16 port, QObject *parent) : QObject(parent)
{
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection,
            this,     &GameServer::onNewConnection);

    if (!m_server->listen(QHostAddress("localhost"), port))
    {
        qDebug() << "Failed to listen to port" << port;
        exit(0);
    }
}

GameServer::~GameServer()
{

}

void GameServer::onNewConnection()
{

}
