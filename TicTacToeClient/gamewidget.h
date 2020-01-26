#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QUuid>

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(quint16 port, const QUuid &gameId, QWidget *parent = nullptr);
    ~GameWidget();

public slots:
    void onReadyRead();
    void onSendToServer(const QByteArray & data);
    void onFieldClicked();
    void onServerReply(const QJsonObject & reply);

private:
    void connectToGame();

private:
    Ui::GameWidget *ui;
    QTcpSocket * m_socket;
    const QUuid m_gameId;
    bool isWhite;
};

#endif // GAMEWIDGET_H
