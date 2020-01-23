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

    std::shared_ptr<Request> request = nullptr;

    QString userLogin = requestObject.value("userLogin").toString();
    QString authToken = requestObject.value("authToken").toString();
    QString userPassword = requestObject.value("userPassword").toString();

    switch (requestType)
    {
    case Request::Type::FindGame:
        request = std::make_shared<FindGameRequest>(sender, userLogin, authToken);
        break;

    case Request::Type::GetStatistics:
        request = std::make_shared<GetStatisticsRequest>(sender, userLogin, authToken);
        break;

    case Request::Type::Test:
        request = std::make_shared<TestRequest>(sender);
        break;

    case Request::Type::SignIn:
        request = std::make_shared<SignInRequest>(sender, userLogin, userPassword);
        break;

    case Request::Type::SignUpUser:
        request = std::make_shared<SignUpUserRequest>(sender, userLogin, userPassword);
        break;

    case Request::Type::Invalid:
        request = std::make_shared<InvalidRequest>(sender);
        break;

    case Request::Type::Unknown:
    default:
        request = std::make_shared<UnknownRequest>(sender);
        break;
    }

    return request;
}
