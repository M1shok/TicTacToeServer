#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H

#include <memory>

class QByteArray;
class Request;
class Connection;

class RequestFactory
{
public:
    RequestFactory();
    ~RequestFactory();

    static std::shared_ptr<Request> createRequest(const QByteArray & data, Connection * sender);
};

#endif // REQUESTFACTORY_H
