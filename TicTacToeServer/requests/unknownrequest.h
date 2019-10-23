#ifndef UNKNOWNREQUEST_H
#define UNKNOWNREQUEST_H

#include "requests/request.h"

class UnknownRequest : public Request
{
public:
    UnknownRequest(QByteArray const &data, Connection* connection);
    ~UnknownRequest() override;
    virtual void handle(RequestHandler *handler) override;
};

#endif // UNKNOWNREQUEST_H
