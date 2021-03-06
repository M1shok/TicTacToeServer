#ifndef UNKNOWNREQUEST_H
#define UNKNOWNREQUEST_H

#include "requests/request.h"

class UnknownRequest : public Request
{
public:
    UnknownRequest(Connection* connection);
    ~UnknownRequest() override;
    virtual Reply handle(RequestHandler *handler) override;
};

#endif // UNKNOWNREQUEST_H
