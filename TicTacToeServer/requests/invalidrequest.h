#ifndef INVALIDREQUEST_H
#define INVALIDREQUEST_H

#include "request.h"

class Connection;

class InvalidRequest : public Request
{
public:
    InvalidRequest(Connection * connection);
    ~InvalidRequest() override;
};

#endif // INVALIDREQUEST_H
