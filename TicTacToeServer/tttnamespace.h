#ifndef TTTNAMESPACE_H
#define TTTNAMESPACE_H

#include <QString>

namespace ttt
{
    const QString connectionName = "TicTacToeConnection";

    namespace User
    {
        const QString tableName = "user";

        const QString id = "id";
        const QString userLogin = "login";
        const QString userPassword = "password";
        const QString authToken = "auth_token";
    }
}

#endif // TTTNAMESPACE_H
