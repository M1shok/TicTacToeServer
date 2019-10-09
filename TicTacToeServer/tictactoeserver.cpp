#include "tictactoeserver.h"

TicTacToeServer::TicTacToeServer(QObject *parent) : QObject(parent)
{
    const int port = 15678;

    m_server = new QTcpServer(this);
    m_requestHandler = new Controller(this);

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
    QTcpSocket* client = m_server->nextPendingConnection();
    Connection *newConnection = new Connection(client, this);

    connect(newConnection,     &Connection::requestOpened,
            m_requestHandler,  &Controller::onRequestOpened);
}
