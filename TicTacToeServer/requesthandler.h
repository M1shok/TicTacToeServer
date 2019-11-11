#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <QObject>

class Request;
class UnknownRequest;
class TestRequest;
class Reply;

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit RequestHandler(QObject *parent = nullptr);

    Reply handle(std::shared_ptr<TestRequest> request);
    Reply handle(std::shared_ptr<UnknownRequest> request);

public slots:
    void onRequestReady(std::shared_ptr<Request> request);
};

#endif // CONTROLLER_H
