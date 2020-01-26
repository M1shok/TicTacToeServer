#include "tictactoeboard.h"


TicTacToeBoard::TicTacToeBoard(int rows, int cols)
    : m_rows(rows)
    , m_cols(cols)
{
    m_isFinished = false;
    m_isWhitesTurn = true;
    m_board.resize(rows);
    for (int i = 0; i < rows; ++i)
    {
        m_board[i].resize(cols);
        for (int j = 0; j < cols; ++j)
        {
            m_board[i][j] = 0;
        }
    }
}

bool TicTacToeBoard::makeMove(int row, int col, char sign)
{
    if (row < m_rows && col < m_cols
            && m_board[row][col] == 0)
    {
        m_board[row][col] = sign;
        m_isWhitesTurn = !m_isWhitesTurn;
        checkFinished(row, col);
        return true;
    }
    return false;
}

bool TicTacToeBoard::isFinished() const
{
    return m_isFinished;
}

bool TicTacToeBoard::isWhitesTurn() const
{
    return m_isWhitesTurn;
}

void TicTacToeBoard::checkFinished(quint32 row, quint32 col)
{
    int toRight = 0;
    int toLeft = 0;
    int toUp = 0;
    int toDown = 0;

    int toUpRight = 0;
    int toUpLeft = 0;
    int toDownRight = 0;
    int toDownLeft = 0;

    int curRow = row;
    int curCol = col + 1;
//
    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        ++curCol;
        ++toRight;
    }

    curRow = row;
    curCol = col - 1;

    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        --curCol;
        ++toLeft;
    }

    curRow = row - 1;
    curCol = col + 1;
//
    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        ++curCol;
        --curRow;
        ++toUpRight;
    }

    curRow = row - 1;
    curCol = col - 1;

    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        --curCol;
        --curRow;
        ++toUpLeft;
    }
//
    curRow = row + 1;
    curCol = col + 1;

    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        ++curCol;
        ++curRow;
        ++toDownRight;
    }

    curRow = row + 1;
    curCol = col - 1;

    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        --curCol;
        ++curRow;
        ++toDownLeft;
    }
//
    curRow = row + 1;
    curCol = col;

    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        ++curRow;
        ++toUp;
    }

    curRow = row - 1;
    curCol = col;

    while (   curRow > 0 && curRow < m_rows
           && curCol > 0 && curCol < m_cols
           && m_board[curRow][curCol] == m_board[row][col])
    {
        --curRow;
        ++toDown;
    }
//

    if (   1 + toUp + toDown >= 5
        || 1 + toLeft + toRight >= 5
        || 1 + toUpLeft + toDownRight >= 5
        || 1 + toDownLeft + toUpRight >= 5)
    {
        m_isFinished = true;
    }
    else
    {
        m_isFinished = false;
    }
}
