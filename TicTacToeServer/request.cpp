#include "request.h"

Request::Request(QByteArray const & requestData)
{
    m_data = requestData;
}
