#include "gamewidget.h"
#include "ui_gamewidget.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QPushButton>

GameWidget::GameWidget(quint16 port, const QUuid & gameId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget),
    m_gameId(gameId)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::readyRead,
            this,     &GameWidget::onReadyRead);

    m_socket->connectToHost("localhost", port);

    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            QPushButton * button = new QPushButton("");
            button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            button->setMinimumSize(QSize(30, 30));
            button->setMaximumSize(button->minimumSize());
            connect (button, &QPushButton::clicked,
                     this,   &GameWidget::onFieldClicked);
            ui->gridLayout->addWidget(button, i, j);
        }
    }

    connectToGame();
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    qDebug() << "Game: Received:" << data;
    QJsonObject reply = QJsonDocument::fromJson(data).object();
    onServerReply(reply);
}

void GameWidget::onSendToServer(const QByteArray &data)
{
    m_socket->write(data, data.size());
}

void GameWidget::onFieldClicked()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
    if (button->text() != "")
        return;

    int row = -1;
    int col = -1;
    QGridLayout * layout = ui->gridLayout;
    int index = layout->indexOf(button);
    int notUsed;
    layout->getItemPosition(index, &row, &col, &notUsed, &notUsed);

    QJsonObject request;
    request.insert("type", 2);
    request.insert("gameId", m_gameId.toString());
    request.insert("row", row);
    request.insert("col", col);
    onSendToServer(QJsonDocument(request).toJson(QJsonDocument::Compact));
}

void GameWidget::onServerReply(const QJsonObject &reply)
{
    int type = reply.value("type").toInt();

    switch (type)
    {
    case 1:
    {
        isWhite = (reply.value("color").toString() == "white");
        qDebug() << "Game started";
        break;
    }
    case 4:
    {
        int row = reply.value("row").toInt();
        int col = reply.value("col").toInt();
        char sign = reply.value("color").toInt();
        QPushButton * button = static_cast<QPushButton*>(ui->gridLayout->itemAtPosition(row, col)->widget());
        button->setText(QString(sign));

        bool isFinished = reply.value("finished").toBool();
        if (isFinished)
        {
            QString winColor = reply.value("winner").toString();
            if ((winColor == "white" && isWhite)
                || (winColor == "black" && !isWhite))
            {
                qDebug() << "You win!";
                QMessageBox::information(this, "Game over!", "You won the game!");
            }
            else
            {
                qDebug() << "You lost!";
                QMessageBox::information(this, "Game over!", "You lost the game!");
            }
        }

        break;
    }
    case 8:
    {
        QString winColor = reply.value("winner").toString();
        if ((winColor == "white" && isWhite)
            || (winColor == "black" && !isWhite))
        {
            qDebug() << "You win!";
        }
        else
        {
            qDebug() << "You lost!";
        }

        qDebug() << "Game finished";
        break;
    }
    }
}

void GameWidget::connectToGame()
{
    QJsonObject request;
    request.insert("type", 1);
    request.insert("gameId", m_gameId.toString());
    onSendToServer(QJsonDocument(request).toJson(QJsonDocument::Compact));
}



