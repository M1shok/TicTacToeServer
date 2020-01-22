#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H


class DatabaseConnector
{
public:
    DatabaseConnector();
    bool createPostgreSqlConnection() const;
    bool declareTables() const;

private:
    bool createTableUsers() const;
};

#endif // DATABASECONNECTOR_H
