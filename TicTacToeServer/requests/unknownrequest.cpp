#include "unknownrequest.h"
#include "requesthandler.h"

UnknownRequest::UnknownRequest(const QByteArray &data, Connection *connection)
    : Request(data, connection)
{

}

UnknownRequest::~UnknownRequest()
{}

void UnknownRequest::handle(RequestHandler *handler)
{
    std::shared_ptr<UnknownRequest> request(this);
    handler->handle(request);
}
