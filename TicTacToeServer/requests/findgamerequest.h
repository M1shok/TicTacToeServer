#ifndef FINDGAMEREQUEST_H
#define FINDGAMEREQUEST_H

#include "request.h"

class FindGameRequest : public Request
{
public:
    FindGameRequest(Connection* sender,
                    const QString &userLogin,
                    const QUuid &authToken);
    ~FindGameRequest() override;

    Reply handle(RequestHandler * handler) override;

    QString userLogin() const;
    QUuid authToken() const;

private:
    const QString m_userLogin;
    const QUuid m_authToken;
};

#endif // FINDGAMEREQUEST_H
