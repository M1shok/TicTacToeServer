#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>

#include <QJsonObject>
#include <QDebug>
#include <QJsonDocument>
#include <QSqlQuery>

#include "requesthandler.h"
#include "requests.h"
#include "reply.h"
#include "connection.h"
#include "tttnamespace.h"




RequestHandler::RequestHandler(QObject *parent) : QObject(parent)
{
    m_model = new QSqlTableModel(this,
                                 QSqlDatabase::database(ttt::connectionName));
}

RequestHandler::~RequestHandler()
{
}

Reply RequestHandler::handle(const TestRequest & /*request*/)
{
    return Reply();
}

Reply RequestHandler::handle(const UnknownRequest & /*request*/)
{
    return Reply();
}

Reply RequestHandler::handle(const InvalidRequest &/*request*/)
{
    return Reply();
}

Reply RequestHandler::handle(const SignInRequest &request)
{
    QJsonObject replyObject;
    replyObject.insert("type", static_cast<int>(Reply::Type::SignIn));

    m_model->setTable(ttt::Users::tableName);
    m_model->setFilter(QString("%1='%2'")
                       .arg(ttt::Users::userLogin)
                       .arg(request.userLogin()));
    m_model->select();

    int rowCount = m_model->rowCount();
    if (rowCount == 0)
    {
        replyObject.insert("status", "fail");
        replyObject.insert("message", "User does not exist.");
    }
    else if (rowCount > 1)
    {
        replyObject.insert("status", "fail");
        replyObject.insert("message", "Internal error. Duplicate logins detected.");
    }
    else
    {
        QSqlRecord user = m_model->record(0);

        if (request.userPassword() == user.value(ttt::Users::userPassword).toString())
        {
            replyObject.insert("status", "success");
            replyObject.insert("authToken",
                               user.value(ttt::Users::authToken).toString());
            replyObject.insert("userLogin",
                               request.userLogin());
        }
        else
        {
            replyObject.insert("status", "fail");
            replyObject.insert("message", "Wrong password.");
        }
    }

    return Reply(QJsonDocument(replyObject)
                 .toJson(QJsonDocument::JsonFormat::Compact));
}

Reply RequestHandler::handle(const SignUpUserRequest &request)
{
    QJsonObject replyObject;
    replyObject.insert("type", static_cast<int>(Reply::Type::SignUpUser));

    m_model->setTable(ttt::Users::tableName);

    QSqlRecord record = m_model->record();

    record.remove(record.indexOf(ttt::Users::id));
    record.setValue(ttt::Users::userLogin,
                    request.userLogin());
    record.setValue(ttt::Users::userPassword,
                    request.userPassword());
    record.setValue(ttt::Users::authToken,
                    QUuid::createUuid().toString());

    if (m_model->insertRecord(-1, record))
    {
        replyObject.insert("status", "success");
        m_model->submitAll();
    }
    else
    {
        replyObject.insert("status", "fail");
        replyObject.insert("message", m_model->lastError().text());
    }

    return Reply(QJsonDocument(replyObject)
                 .toJson(QJsonDocument::JsonFormat::Compact));
}

Reply RequestHandler::handle(const FindGameRequest &request)
{
    QJsonObject replyObject;
    replyObject.insert("type", static_cast<int>(Reply::Type::FindGame));

    m_model->setTable(ttt::Users::tableName);
    m_model->setFilter(QString("%1='%2'"
                               " and "
                               "%3='%4'")
                       .arg(ttt::Users::userLogin)
                       .arg(request.userLogin())
                       .arg(ttt::Users::authToken)
                       .arg(request.authToken().toString()));
    m_model->select();

    int rowCount = m_model->rowCount();
    if (rowCount == 0)
    {
        replyObject.insert("status", "fail");
        replyObject.insert("message", "Auth failure");
    }
    else if (rowCount > 1)
    {
        replyObject.insert("status", "fail");
        replyObject.insert("message",
                           "Internal error. Duplicate logins detected.");
    }
    else
    {
        replyObject.insert("status", "success");
        replyObject.insert("message", "Searching for opponent");
        addUserToFindGame(request.sender());
    }

    return Reply();
    return Reply(QJsonDocument(replyObject)
                .toJson(QJsonDocument::JsonFormat::Compact));
}

Reply RequestHandler::handle(const GetStatisticsRequest &/*request*/)
{
    return Reply();
}

void RequestHandler::onRequestReady(std::shared_ptr<Request> request)
{
    Connection * connection = static_cast<Connection*>(sender());

    Reply reply = request->handle(this);

    connection->onReplyReady(reply);
}

void RequestHandler::addUserToFindGame(Connection *connection)
{
    Connection * opponent = findOpponent();
    if (opponent != nullptr)
    {
        m_matchMaking.removeOne(opponent);

        QJsonObject replyObject;
        replyObject.insert("type", static_cast<int>(Reply::Type::GameFound));
        replyObject.insert("status", "success");
        replyObject.insert("gameServerIP", "localhost");
        replyObject.insert("gameServerPort", 3232);
        replyObject.insert("gameId", QUuid::createUuid().toString());

        Reply reply(QJsonDocument(replyObject)
                    .toJson(QJsonDocument::JsonFormat::Compact));
        opponent->onReplyReady(reply);
        connection->onReplyReady(reply);
    }
    else
    {
        m_matchMaking.push_back(connection);
    }
}

Connection *RequestHandler::findOpponent() const
{
    if (m_matchMaking.empty())
        return nullptr;
    return m_matchMaking.first();
}
