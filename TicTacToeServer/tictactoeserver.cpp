#include <QCoreApplication>
#include <QTcpServer>
#include <iostream>
#include "tictactoeserver.h"
#include "requesthandler.h"
#include "connection.h"

TicTacToeServer::TicTacToeServer(QObject *parent) : QObject(parent)
{
    const int port = 15678;

    m_server = new QTcpServer(this);
    m_requestHandler = new RequestHandler(this);

    connect(m_server, &QTcpServer::newConnection,
            this,     &TicTacToeServer::onNewConnection);

    if (!m_server->listen(QHostAddress::Any, port))
    {
        std::cerr << "Server is not started. Cannot listn to port " << port << ".\n";
        exit(0);
    }
}

void TicTacToeServer::onNewConnection()
{
    QTcpSocket * client = m_server->nextPendingConnection();
    Connection * newConnection = new Connection(client, this);

    connect(newConnection,     &Connection::requestReady,
            m_requestHandler,  &RequestHandler::onRequestReady);
}
