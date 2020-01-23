#include "reply.h"

Reply::Reply(QByteArray const & replyData)
{
    m_data = replyData;
}

QByteArray Reply::data() const
{
    return m_data;
}
