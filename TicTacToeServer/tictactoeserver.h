#ifndef TICTACTOESERVER_H
#define TICTACTOESERVER_H

#include <QObject>

class Connection;
class RequestHandler;
class QTcpServer;

class TicTacToeServer : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToeServer(quint16 port, QObject *parent = nullptr);

public slots:
    void onNewConnection();
//    void onAcceptError(QAbstractSocket::SocketError socketError);

private:
    RequestHandler * m_requestHandler;
    QTcpServer * m_server;
};

#endif // TICTACTOESERVER_H
