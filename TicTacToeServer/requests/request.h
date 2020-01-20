#ifndef REQUEST_H
#define REQUEST_H

#include <QByteArray>

class RequestHandler;
class Connection;
class Reply;

class Request
{
public:
    Request(QByteArray const & requestData, Connection* sender);
    virtual ~Request() = 0;
    virtual Reply handle(RequestHandler* handler) = 0;

    enum class Type
    {
        InvalidRequest = 0,
        UnknownRequest = 1000
    };

private:
    QByteArray m_data;
    Connection* m_sender;
};

#endif // REQUEST_H
