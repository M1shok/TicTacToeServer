#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "tttnamespace.h"
#include "databaseconnector.h"

DatabaseConnector::DatabaseConnector()
{

}

bool DatabaseConnector::createPostgreSqlConnection() const
{
    QSqlDatabase connection = QSqlDatabase::addDatabase("QPSQL", ttt::connectionName);

    connection.setHostName("localhost");
    connection.setDatabaseName(ttt::databaseName);
    connection.setUserName("docker");
    connection.setPassword("password");
    connection.setPort(5432);
    bool opened = connection.open();

    if (connection.lastError().isValid())
        qDebug() << connection.lastError();

    declareTables();

    return opened;
}

bool DatabaseConnector::declareTables() const
{
    bool allTablesCreated = true;

    allTablesCreated = allTablesCreated && createTableUsers();

    return allTablesCreated;
}

bool DatabaseConnector::createTableUsers() const
{
    QString queryString = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                  " %2 SERIAL, "
                                  " %3 VARCHAR(32) UNIQUE, "
                                  " %4 VARCHAR(32), "
                                  " %5 VARCHAR(32)"
                                  ");")
            .arg(ttt::Users::tableName)
            .arg(ttt::Users::id)
            .arg(ttt::Users::userLogin)
            .arg(ttt::Users::userPassword)
            .arg(ttt::Users::authToken);

    QSqlDatabase connection = QSqlDatabase::database(ttt::connectionName);
    QSqlQuery query(connection);

    if (!query.exec(queryString))
    {
        qDebug() << query.lastError();
        return false;
    }

    return true;
}
