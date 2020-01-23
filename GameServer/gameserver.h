#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QTcpServer>

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(quint16 port, QObject *parent = nullptr);
    ~GameServer() override;

public slots:
    void onNewConnection();

private:
    QTcpServer * m_server;
};

#endif // GAMESERVER_H
