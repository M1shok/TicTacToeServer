#include "testrequest.h"

#include "requesthandler.h"
#include "reply.h"

TestRequest::TestRequest(Connection* sender)
    : Request(sender)
{

}

TestRequest::~TestRequest()
{

}

Reply TestRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}
