#include "testrequest.h"

#include "requesthandler.h"
#include "reply.h"

TestRequest::TestRequest(QByteArray &data, Connection* sender)
    : Request(data, sender)
{

}

TestRequest::~TestRequest()
{

}

Reply TestRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}
