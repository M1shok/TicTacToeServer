#include "signinrequest.h"
#include "requesthandler.h"
#include "reply.h"

SignInRequest::SignInRequest(Connection *sender,
                             const QString &userLogin,
                             const QString &userPassword)
    : Request(sender)
    , m_userLogin(userLogin)
    , m_userPassword(userPassword)
{

}

SignInRequest::~SignInRequest()
{

}

Reply SignInRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}

QString SignInRequest::userPassword() const
{
    return m_userPassword;
}

QString SignInRequest::userLogin() const
{
    return m_userLogin;
}
