#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "tttnamespace.h"
#include "databaseconnector.h"

DatabaseConnector::DatabaseConnector()
{

}

bool DatabaseConnector::createPostgreSqlConnection() const
{
    QSqlDatabase connection = QSqlDatabase::addDatabase("QPSQL", ttt::connectionName);

    connection.setHostName("localhost");
    connection.setDatabaseName(MM::Database::databaseName);
    connection.setUserName("docker");
    connection.setPassword("password");
    connection.setPort(5432);
    bool opened = connection.open();

    if (connection.lastError().isValid())
        qDebug() << connection.lastError();

    return opened;
}

bool DatabaseConnector::declareTables() const
{
    bool allTablesCreated = true;

    allTablesCreated = allTablesCreated && createTableUser();

    return allTablesCreated;
}

bool DatabaseConnector::createTableUser() const
{
    QString queryString = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                  " %2 SERIAL, "
                                  " %3 VARCHAR(32) UNIQUE, "
                                  " %4 VARCHAR(32), "
                                  " %5 VARCHAR(32);")
            .arg(ttt::User::tableName)
            .arg(ttt::User::id)
            .arg(ttt::User::userLogin)
            .arg(ttt::User::userPassword)
            .arg(ttt::User::authToken);

    QSqlDatabase connection = QSqlDatabase::database(ttt::connectionName);
    QSqlQuery query(connection);

    if (!query.exec(queryString))
    {
        qDebug() << query.lastError();
        return false;
    }

    return true;
}
