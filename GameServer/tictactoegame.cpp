#include "tictactoegame.h"

#include "connection.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

TicTacToeGame::TicTacToeGame(const QUuid &id, QObject *parent)
    : QObject(parent)
    , m_gameId(id)
    , m_whitePlayer(nullptr)
    , m_blackPlayer(nullptr)
    , m_board(15, 15)
{

}

void TicTacToeGame::onClientConnected(Connection *connection)
{
    if (m_whitePlayer == nullptr)
    {
        m_whitePlayer = connection;
    }
    else
    {
        m_blackPlayer = connection;
        QJsonObject wreply;
        QJsonObject breply;

        wreply.insert("type", 1);
        breply.insert("type", 1);

        wreply.insert("color", "white");
        breply.insert("color", "black");

        m_whitePlayer->onReplyReady(QJsonDocument(wreply).toJson(QJsonDocument::Compact));
        m_blackPlayer->onReplyReady(QJsonDocument(breply).toJson(QJsonDocument::Compact));
    }
}

bool TicTacToeGame::makeMove(int row, int col, Connection *connection)
{
    QJsonObject reply;
//    reply.insert("status", "")
    char sign = 0;
    if (m_board.isWhitesTurn())
    {
        if (connection == m_whitePlayer)
        {
            sign = 'X';
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (connection == m_blackPlayer)
        {
            sign = '0';
        }
        else
        {
            return false;
        }
    }

    if (m_board.makeMove(row, col, sign))
    {
        reply.insert("type", 4);
        reply.insert("row", row);
        reply.insert("col", col);
        reply.insert("color", sign);
        if (m_board.isFinished())
        {
            reply.insert("finished", true);
            if (connection == m_whitePlayer)
            {
                reply.insert("winner", "white");
            }
            else
            {
                reply.insert("winner", "black");
            }
        }
        else
        {
            reply.insert("finished", false);
        }
        notifyPlayers(reply);
        return true;
    }
    else
    {
        return false;
    }
}

bool TicTacToeGame::resign(Connection *connection)
{
    QJsonObject reply;
    reply.insert("type", 8);
    if (connection == m_whitePlayer)
    {
        reply.insert("winner", "black");
    }
    else
    {
        reply.insert("winner", "white");
    }
    notifyPlayers(reply);
    return true;
}

void TicTacToeGame::notifyPlayers(const QJsonObject & reply)
{
    auto data = QJsonDocument(reply).toJson(QJsonDocument::Compact);
    m_whitePlayer->onReplyReady(data);
    m_blackPlayer->onReplyReady(data);
}
