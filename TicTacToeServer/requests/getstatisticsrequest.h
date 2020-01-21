#ifndef GETSTATISTICSREQUEST_H
#define GETSTATISTICSREQUEST_H

#include "request.h"

class GetStatisticsRequest : public Request
{
public:
    GetStatisticsRequest(Connection * sender,
                         const QString &userLogin,
                         const QUuid &authToken);
    ~GetStatisticsRequest() override;

    Reply handle(RequestHandler *handler) override;

    QString userLogin() const;
    QUuid authToken() const;

private:
    const QString m_userLogin;
    const QUuid m_authToken;
};

#endif // GETSTATISTICSREQUEST_H
