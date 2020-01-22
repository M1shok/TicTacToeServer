#include "findgamerequest.h"
#include "requesthandler.h"
#include "reply.h"

FindGameRequest::FindGameRequest(Connection *sender, const QString &userLogin, const QUuid &authToken)
    : Request(sender)
    , m_userLogin(userLogin)
    , m_authToken(authToken)
{

}

FindGameRequest::~FindGameRequest()
{

}

Reply FindGameRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}

QUuid FindGameRequest::authToken() const
{
    return m_authToken;
}

QString FindGameRequest::userLogin() const
{
    return m_userLogin;
}
