#ifndef SIGNINREQUEST_H
#define SIGNINREQUEST_H

#include "request.h"

class SignInRequest : public Request
{
public:
    SignInRequest(Connection * sender,
                  const QString & userLogin,
                  const QString & userPassword);
    ~SignInRequest() override;

    Reply handle(RequestHandler *handler) override;
    QString login() const;
    QString password() const;

private:
    const QString m_userLogin;
    const QString m_userPassword;
};

#endif // SIGNINREQUEST_H
