#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QTcpSocket>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "authorizationdialog.h"
#include "registrationdialog.h"

#include "networktypes.h"
#include "gamewidget.h"

TicTacToeClient::TicTacToeClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::readyRead,
            this,     &TicTacToeClient::onReadyRead);
    m_socket->connectToHost("localhost", 2323);

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,
            this,          &TicTacToeClient::onTabCloseRequested);

    if (!m_socket->waitForConnected())
    {
        qDebug() << "Connection was not established.";
        exit(-1);
    }
    onLogOut();
    ui->tabWidget->clear();
}

TicTacToeClient::~TicTacToeClient()
{
    delete ui;
}


void TicTacToeClient::on_pbSignIn_clicked()
{
    AuthorizationDialog dialog;

    if (dialog.exec() == QDialog::Accepted)
    {
        QJsonObject requestObject;

        requestObject.insert("requestType",
                             static_cast<int>(RequestType::SignIn));
        requestObject.insert("userLogin", dialog.userLogin());
        requestObject.insert("userPassword", dialog.userPassword());

        sendRequestToServer(QJsonDocument(requestObject)
                            .toJson(QJsonDocument::JsonFormat::Compact));
    }
}

void TicTacToeClient::on_pbSignUp_clicked()
{
    RegistrationDialog dialog;

    if (dialog.exec() == QDialog::Accepted)
    {
        QJsonObject requestObject;

        requestObject.insert("requestType",
                             static_cast<int>(RequestType::SignUpUser));
        requestObject.insert("userLogin", dialog.userLogin());
        requestObject.insert("userPassword", dialog.userPassword());

        sendRequestToServer(QJsonDocument(requestObject)
                            .toJson(QJsonDocument::JsonFormat::Compact));
    }
}

void TicTacToeClient::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    qDebug() << "Received: " << data;
    onServerReply(data);
}

void TicTacToeClient::onServerReply(const QByteArray &reply)
{
    QJsonObject replyObject
            = QJsonDocument::fromJson(reply).object();

    ReplyType replyType
            = static_cast<ReplyType>(replyObject.value("type").toInt());
    switch (replyType)
    {
    case ReplyType::Test:
    case ReplyType::Unknown:
    case ReplyType::Invalid:
    case ReplyType::GetStatistics:
        qDebug() << "Not implemented";
        break;

    case ReplyType::SignIn:
        onSignInReply(replyObject);
        break;

    case ReplyType::SignUpUser:
        onSignUpReply(replyObject);
        break;

    case ReplyType::FindGame:
        onFindGameReply(replyObject);
        break;

    case ReplyType::GameFound:
        onGameFoundReply(replyObject);
        break;
    }
}

void TicTacToeClient::sendRequestToServer(const QByteArray &data)
{
    m_socket->write(data, data.size());
}

void TicTacToeClient::onSignUpReply(const QJsonObject &replyObject)
{
    QString status = replyObject.value("status").toString();
    if (status == "success")
    {
        QMessageBox::information(this,
                                 "Registration",
                                 "Registration successful");
    }
    else
    {
        QString message = replyObject.value("message").toString();
        QMessageBox::information(this,
                                 "Registration",
                                 "Registration failed. Message: "
                                 + message);
    }
}

void TicTacToeClient::onSignInReply(const QJsonObject &replyObject)
{
    QString status = replyObject.value("status").toString();
    if (status == "success")
    {
        m_authToken = replyObject.value("authToken").toString();
        m_userLogin = replyObject.value("userLogin").toString();
        onLogIn();
    }
    else
    {
        QString message = replyObject.value("message").toString();
        QMessageBox::information(this,
                                 "Authorization",
                                 "Authorization failed. Message: "
                                 + message);
    }
}

void TicTacToeClient::onGameFoundReply(const QJsonObject &replyObject)
{
    QString status = replyObject.value("status").toString();
    QString gameId = replyObject.value("gameId").toString();
    ui->tabWidget->addTab(new GameWidget(3232, gameId), "Game");
}

void TicTacToeClient::onFindGameReply(const QJsonObject &replyObject)
{
    QString status = replyObject.value("status").toString();
    if (status != "success")
    {
        QString message = replyObject.value("message").toString();
        QMessageBox::information(this,
                                 "Authorization",
                                 "Authorization failed. Message: "
                                 + message);
    }
}

void TicTacToeClient::onTabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void TicTacToeClient::onLogIn()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void TicTacToeClient::onLogOut()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void TicTacToeClient::on_pbLogOut_clicked()
{
    onLogOut();
}

void TicTacToeClient::on_pbFindGame_clicked()
{
    QJsonObject requestObject;

    requestObject.insert("requestType",
                         static_cast<int>(RequestType::FindGame));
    requestObject.insert("userLogin", m_userLogin);
    requestObject.insert("authToken", m_authToken);

    sendRequestToServer(QJsonDocument(requestObject)
                        .toJson(QJsonDocument::JsonFormat::Compact));
}
