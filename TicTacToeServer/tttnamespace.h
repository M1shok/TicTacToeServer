#ifndef TTTNAMESPACE_H
#define TTTNAMESPACE_H

#include <QString>

namespace ttt
{
    const QString connectionName = "TicTacToeConnection";
    const QString databaseName = "tic_tac_toe";
    namespace Users
    {
        const QString tableName = "users";

        const QString id = "id";
        const QString userLogin = "login";
        const QString userPassword = "password";
        const QString authToken = "auth_token";
    }
}

#endif // TTTNAMESPACE_H
