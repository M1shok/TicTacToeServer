#include "gameserver.h"
#include "connection.h"

#include <QJsonDocument>
#include <QJsonObject>

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
    QTcpSocket * client = m_server->nextPendingConnection();
    Connection * newConnection = new Connection(client, this);

    connect(newConnection,     &Connection::requestReady,
            this,              &GameServer::onRequestReady);
}

void GameServer::onRequestReady(QByteArray data)
{
    Connection * client = static_cast<Connection*>(sender());

    QJsonObject requestObject = QJsonDocument::fromJson(data).object();

    int requestType = requestObject.value("type").toInt();
    QJsonObject reply;
    switch (requestType)
    {
    case 1:
        reply = onRequestConnectToGame(requestObject, client);
        break;
    case 2:
        reply = onRequestMakeMove(requestObject, client);
        break;
    case 3:
        reply = onRequestResign(requestObject, client);
        break;
    default:
        break;
    }

    if (!reply.empty())
    {
        client->onReplyReady(QJsonDocument(reply)
                             .toJson(QJsonDocument::Compact));
    }
}

QJsonObject GameServer::onRequestConnectToGame(const QJsonObject &request, Connection *connection)
{
    QJsonObject reply;
    QUuid gameId = request.value("gameId").toString();

    if (m_gameMap.contains(gameId))
    {
        m_gameMap[gameId]->onClientConnected(connection);
    }
    else
    {
        TicTacToeGame * game = new TicTacToeGame(gameId);
        m_gameMap[gameId] = game;
        game->onClientConnected(connection);
    }
    return reply;
}

QJsonObject GameServer::onRequestMakeMove(const QJsonObject &request, Connection *connection)
{
    QJsonObject reply;
    QUuid gameId = request.value("gameId").toString();
    int row = request.value("row").toInt();
    int col = request.value("col").toInt();

    if (m_gameMap.contains(gameId))
    {
        if (m_gameMap[gameId]->makeMove(row, col, connection))
        {
//            reply.insert("status", "success");
        }
        else
        {
            reply.insert("type", 7);
            reply.insert("status", "fail");
            reply.insert("message", "impossible move");
        }
    }
    else
    {
        reply.insert("status", "fail");
        reply.insert("message", "no such game");
    }
    return reply;
}

QJsonObject GameServer::onRequestResign(const QJsonObject &request, Connection *connection)
{
    QJsonObject reply;
    QUuid gameId = request.value("gameId").toString();
    if (m_gameMap.contains(gameId))
    {
        m_gameMap[gameId]->resign(connection);
    }
    else
    {
        reply.insert("status", "fail");
        reply.insert("message", "no such game");
    }
    return reply;
}
