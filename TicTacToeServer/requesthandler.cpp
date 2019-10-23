#include "requesthandler.h"
#include "requests/request.h"

RequestHandler::RequestHandler(QObject *parent) : QObject(parent)
{

}

void RequestHandler::handle(std::shared_ptr<Request> request)
{
    request->handle(this);
}

void RequestHandler::handle(std::shared_ptr<UnknownRequest> request)
{

}

void RequestHandler::onRequestReady(std::shared_ptr<Request> request)
{
    handle(request);
}
