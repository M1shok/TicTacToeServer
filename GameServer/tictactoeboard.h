#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include <QVector>

class TicTacToeBoard
{
public:
    TicTacToeBoard(int rows, int cols);

    bool makeMove(int row, int col, char sign);
    bool isFinished() const;
    bool isWhitesTurn() const;

private:
    void checkFinished(quint32 row, quint32 col);

private:
    const int m_rows;
    const int m_cols;
    bool m_isFinished;
    bool m_isWhitesTurn;

    QVector<QVector<char>> m_board;
};

#endif // TICTACTOEBOARD_H
