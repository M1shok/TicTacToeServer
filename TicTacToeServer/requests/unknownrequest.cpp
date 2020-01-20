#include "unknownrequest.h"
#include "requesthandler.h"
#include "reply.h"

UnknownRequest::UnknownRequest(Connection *connection)
    : Request(connection)
{

}

UnknownRequest::~UnknownRequest()
{}

Reply UnknownRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}
