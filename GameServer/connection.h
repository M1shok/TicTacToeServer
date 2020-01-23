#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket * client, QObject *parent = nullptr);

public slots:
    void onReadyRead();
    void onReplyReady(const QByteArray & reply);

signals:
    void onRequestReady(QByteArray data);

private:
    QTcpSocket * m_client;
};

#endif // CONNECTION_H
