#ifndef REQUEST_H
#define REQUEST_H

#include <QByteArray>
#include <QJsonDocument>

class Request
{
public:
    Request(QByteArray const & requestData);

    enum class Type
    {
        InvalidRequest = 0,
        UnknownRequest = 1000
    };

private:
    QByteArray m_data;
    Type m_type;
};

#endif // REQUEST_H
