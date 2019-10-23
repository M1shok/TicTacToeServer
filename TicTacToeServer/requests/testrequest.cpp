#include "testrequest.h"

TestRequest::TestRequest(QByteArray &data, Connection* sender)
    : Request(data, sender)
{

}

TestRequest::~TestRequest()
{

}

void TestRequest::handle(RequestHandler *handler)
{

}
