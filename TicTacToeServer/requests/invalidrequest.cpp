#include "invalidrequest.h"
#include "requesthandler.h"

InvalidRequest::InvalidRequest(Connection *connection)
    : Request(connection)
{

}

Reply InvalidRequest::handle(RequestHandler *handler)
{
    handler->handle(*this);
}
