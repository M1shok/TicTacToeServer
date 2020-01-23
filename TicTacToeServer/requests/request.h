#ifndef REQUEST_H
#define REQUEST_H

#include <QByteArray>
#include <QUuid>

class RequestHandler;
class Connection;
class Reply;

class Request
{
public:
    Request(Connection* sender);
    virtual ~Request() = 0;
    virtual Reply handle(RequestHandler* handler) = 0;

    enum class Type
    {
        Invalid = 0,
        Test = 1,
        FindGame = 2,
        SignIn = 3,
        SignUpUser = 4,
        GetStatistics = 5,
        Unknown = 1000
    };

    Connection * sender() const;

private:
    Connection* m_sender;
};

#endif // REQUEST_H
