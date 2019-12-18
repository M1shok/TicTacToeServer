#include "requesthandler.h"
#include "requests/request.h"
#include "reply.h"

RequestHandler::RequestHandler(QObject *parent) : QObject(parent)
{

}

Reply RequestHandler::handle(std::shared_ptr<TestRequest> request)
{

}

Reply RequestHandler::handle(std::shared_ptr<UnknownRequest> request)
{

}

void RequestHandler::onRequestReady(std::shared_ptr<Request> request)
{
    request->handle(this);
}
