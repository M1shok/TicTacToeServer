#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include "request.h"

#include <memory>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket *client, QObject *parent = nullptr);
    ~Connection();

public slots:
    void onReadyRead();

signals:
    void requestOpened(std::shared_ptr<Request> const request);

private:
    QTcpSocket *m_client;
};

#endif // CONNECTION_H
