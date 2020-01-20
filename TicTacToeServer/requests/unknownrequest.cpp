#include "unknownrequest.h"
#include "requesthandler.h"
#include "reply.h"

UnknownRequest::UnknownRequest(const QByteArray &data, Connection *connection)
    : Request(data, connection)
{

}

UnknownRequest::~UnknownRequest()
{}

Reply UnknownRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}
