#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <memory>

class Reply;
class QTcpSocket;
class TestRequest;
class UnknownRequest;
class Request;

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket *client, QObject *parent = nullptr);
    ~Connection();

public slots:
    void onReadyRead();
    void onReplyReady(std::shared_ptr<Reply> reply);

signals:
    void requestReady(std::shared_ptr<Request> request);

private:
    QTcpSocket *m_client;
};

#endif // CONNECTION_H
