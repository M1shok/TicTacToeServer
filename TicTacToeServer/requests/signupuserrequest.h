#ifndef SIGNUPUSERREQUEST_H
#define SIGNUPUSERREQUEST_H

#include "request.h"

class SignUpUserRequest : public Request
{
public:
    SignUpUserRequest(Connection * sender,
                      const QString & userLogin,
                      const QString & userPassword);
    ~SignUpUserRequest() override;

    Reply handle(RequestHandler *handler) override;
    QString userLogin() const;
    QString userPassword() const;

private:
    const QString m_userLogin;
    const QString m_userPassword;
};

#endif // SIGNUPUSERREQUEST_H
