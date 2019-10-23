#include "request.h"

Request::Request(QByteArray const & requestData, Connection *sender)
{
    m_data = requestData;
    m_sender = sender;
}

Request::~Request()
{

}

