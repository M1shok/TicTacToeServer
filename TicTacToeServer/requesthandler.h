#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <QObject>

class Request;
class Reply;

class UnknownRequest;
class TestRequest;
class InvalidRequest;

class SignInRequest;
class SignUpUserRequest;
class FindGameRequest;
class GetStatisticsRequest;

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit RequestHandler(QObject *parent = nullptr);

    Reply handle(const TestRequest &request);
    Reply handle(const UnknownRequest &request);
    Reply handle(const InvalidRequest &request);

    Reply handle(const SignInRequest &request);
    Reply handle(const SignUpUserRequest &request);
    Reply handle(const FindGameRequest &request);
    Reply handle(const GetStatisticsRequest &request);

public slots:
    void onRequestReady(std::shared_ptr<Request> request);
};

#endif // CONTROLLER_H
