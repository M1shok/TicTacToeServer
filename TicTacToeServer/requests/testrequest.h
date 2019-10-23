#ifndef TESTREQUEST_H
#define TESTREQUEST_H

#include "request.h"

class TestRequest : public Request
{
public:
    TestRequest(QByteArray &data, Connection* sender);
    ~TestRequest() override;
    void handle(RequestHandler *handler) override;
};

#endif // TESTREQUEST_H
