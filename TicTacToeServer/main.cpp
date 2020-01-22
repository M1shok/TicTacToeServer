#include <QCoreApplication>

#include "tictactoeserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TicTacToeServer server(2323);

    return a.exec();
}
