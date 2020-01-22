#include <QJsonObject>
#include <QJsonDocument>

#include "requestfactory.h"
#include "requests/request.h"
#include "requests.h"

RequestFactory::RequestFactory()
{

}

RequestFactory::~RequestFactory()
{

}

std::shared_ptr<Request> RequestFactory::createRequest(const QByteArray &data, Connection * sender)
{
    QJsonDocument document = QJsonDocument::fromJson(data);

    if (!document.isObject())
    {
        return std::make_shared<InvalidRequest>(sender);
    }

    QJsonObject requestObject = document.object();

    Request::Type requestType =
            static_cast<Request::Type>(requestObject.value("requestType").toInt());

    switch (requestType)
    {
    case Request::Type::FindGame:

    case Request::Type::GetStatistics:

    case Request::Type::Test:

    case Request::Type::SignIn:

    case Request::Type::SignUpUser:
    case Request::Type::Unknown:
    case Request::Type::Invalid:
        break;
    }
    return std::make_shared<UnknownRequest>(sender);
}
