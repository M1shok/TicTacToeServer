#ifndef TICTACTOESERVER_H
#define TICTACTOESERVER_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include "controller.h"
#include "connection.h"

#include <iostream>
#include <memory>

class TicTacToeServer : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToeServer(QObject *parent = nullptr);

public slots:
    void onNewConnection();
//    void onAcceptError(QAbstractSocket::SocketError socketError);

private:
    Controller * m_requestHandler;
    QTcpServer * m_server;
};

#endif // TICTACTOESERVER_H
