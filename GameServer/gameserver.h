#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QJsonObject>
#include <QObject>
#include <QTcpServer>

#include "tictactoegame.h"

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(quint16 port, QObject *parent = nullptr);
    ~GameServer() override;

public slots:
    void onNewConnection();
    void onRequestReady(QByteArray data);

    QJsonObject onRequestConnectToGame(const QJsonObject & request, Connection * connection);
    QJsonObject onRequestMakeMove(const QJsonObject & request, Connection * connection);
    QJsonObject onRequestResign(const QJsonObject & request, Connection * connection);

private:
    QMap<QUuid, TicTacToeGame*> m_gameMap;
    QTcpServer * m_server;
};

#endif // GAMESERVER_H
