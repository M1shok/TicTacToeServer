#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include <QMutex>
#include <QObject>
#include <QUuid>
#include "tictactoeboard.h"
class Connection;

class TicTacToeGame : public QObject
{
    Q_OBJECT
public:
    explicit TicTacToeGame(const QUuid & id, QObject *parent = nullptr);

    void onClientConnected(Connection * connection);
    bool makeMove(int row, int col, Connection * connection);
    bool resign(Connection * connection);

private:
    void notifyPlayers(const QJsonObject & reply);
    void endGame();

private:
    const QUuid m_gameId;
    Connection * m_whitePlayer;
    Connection * m_blackPlayer;
    TicTacToeBoard m_board;
    QMutex m_mutex;
};

#endif // TICTACTOEGAME_H
