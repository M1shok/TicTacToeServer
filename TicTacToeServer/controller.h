#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <memory>

#include "connection.h"
#include "request.h"

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit RequestHandler(QObject *parent = nullptr);

public slots:
    void onRequestOpened(std::shared_ptr<Request> const request);
};

#endif // CONTROLLER_H
