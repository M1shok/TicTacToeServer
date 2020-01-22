#include "invalidrequest.h"
#include "requesthandler.h"
#include "reply.h"

InvalidRequest::InvalidRequest(Connection *connection)
    : Request(connection)
{

}

InvalidRequest::~InvalidRequest()
{

}

Reply InvalidRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}
