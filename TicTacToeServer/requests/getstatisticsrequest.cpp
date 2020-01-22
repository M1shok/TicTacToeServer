#include "getstatisticsrequest.h"
#include "requesthandler.h"
#include "reply.h"

GetStatisticsRequest::GetStatisticsRequest(Connection *sender, const QString &userLogin, const QUuid &authToken)
    : Request(sender)
    , m_userLogin(userLogin)
    , m_authToken(authToken)
{

}

GetStatisticsRequest::~GetStatisticsRequest()
{

}

Reply GetStatisticsRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}

QUuid GetStatisticsRequest::authToken() const
{
    return m_authToken;
}

QString GetStatisticsRequest::userLogin() const
{
    return m_userLogin;
}
