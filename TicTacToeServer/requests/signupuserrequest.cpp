#include "signupuserrequest.h"
#include "requesthandler.h"
#include "reply.h"

SignUpUserRequest::SignUpUserRequest(Connection *sender,
                                     const QString &userLogin,
                                     const QString &userPassword)
    : Request(sender)
    , m_userLogin(userLogin)
    , m_userPassword(userPassword)
{

}

SignUpUserRequest::~SignUpUserRequest()
{

}

Reply SignUpUserRequest::handle(RequestHandler *handler)
{
    return handler->handle(*this);
}

QString SignUpUserRequest::userLogin() const
{
    return m_userLogin;
}

QString SignUpUserRequest::userPassword() const
{
    return m_userPassword;
}
