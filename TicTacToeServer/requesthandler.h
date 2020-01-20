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

    Reply handle(const TestRequest &request);
    Reply handle(const UnknownRequest &request);

public slots:
    void onRequestReady(std::shared_ptr<Request> request);
};

#endif // CONTROLLER_H
