#ifndef REQUEST_H
#define REQUEST_H

#include <QByteArray>

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
        Unknown = 1000
    };

private:
    Connection* m_sender;
};

#endif // REQUEST_H
