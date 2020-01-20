#ifndef REPLY_H
#define REPLY_H

#include <QByteArray>

class Reply
{
public:
    Reply(QByteArray const & replyData = QByteArray());

private:
    QByteArray m_data;
};

#endif // REPLY_H
