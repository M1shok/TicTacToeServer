#ifndef TESTREQUEST_H
#define TESTREQUEST_H

#include "request.h"

class TestRequest : public Request
{
public:
    TestRequest(Connection* sender);
    ~TestRequest() override;
    Reply handle(RequestHandler *handler) override;
};

#endif // TESTREQUEST_H
