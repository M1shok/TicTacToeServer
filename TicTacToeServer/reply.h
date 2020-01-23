#ifndef REPLY_H
#define REPLY_H

#include <QByteArray>

class Reply
{
public:
    enum class Type
    {
        Unknown = 0,
        Invalid = 1,
        Test = 2,
        FindGame = 3,
        GameFound = 4,
        SignIn = 5,
        SignUpUser = 6,
        GetStatistics = 7
    };

public:
    Reply(QByteArray const & replyData = QByteArray());

    QByteArray data() const;

private:
    QByteArray m_data;
};

#endif // REPLY_H
