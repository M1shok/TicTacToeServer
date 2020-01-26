#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTcpSocket;

class TicTacToeClient : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToeClient(QWidget *parent = nullptr);
    ~TicTacToeClient();

private slots:
    void on_pbSignIn_clicked();
    void on_pbSignUp_clicked();

    void on_pbLogOut_clicked();
    void on_pbFindGame_clicked();

    void onReadyRead();
    void onServerReply(const QByteArray & reply);

    void sendRequestToServer(const QByteArray & data);

    void onSignUpReply(const QJsonObject & replyObject);
    void onSignInReply(const QJsonObject & replyObject);
    void onGameFoundReply(const QJsonObject & replyObject);
    void onFindGameReply(const QJsonObject & replyObject);
    void onTabCloseRequested(int index);
    void onLogIn();
    void onLogOut();


private:
    Ui::MainWindow *ui;
    QTcpSocket * m_socket;
    QString m_authToken;
    QString m_userLogin;
};
#endif // MAINWINDOW_H
