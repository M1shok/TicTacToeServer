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
        return std::make_shared<InvalidRequest>();
    }

    QJsonObject requestObject = document.object();

    Request::Type requestType =
            static_cast<Request::Type>(requestObject.value("requestType").toInt());

    switch (requestType)
    {
    }
    return std::make_shared<UnknownRequest>();
}
