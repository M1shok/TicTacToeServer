#include <QCoreApplication>

#include "gameserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameServer server(3232);
    return a.exec();
}
