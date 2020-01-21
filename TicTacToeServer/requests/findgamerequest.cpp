#include "findgamerequest.h"
#include "requesthandler.h"

FindGameRequest::FindGameRequest(Connection *sender, const QString &userLogin, const QUuid &authToken)
    : Request(sender)
    , m_login(userLogin)
    , m_authToken(authToken)
{

}

FindGameRequest::~FindGameRequest()
{

}

Reply FindGameRequest::handle(RequestHandler *handler)
{
    handler->handle(*this);
}

QUuid FindGameRequest::authToken() const
{
    return m_authToken;
}

QString FindGameRequest::userLogin() const
{
    return m_userLogin;
}
