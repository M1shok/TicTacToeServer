#include "request.h"

Request::Request(Connection *sender)
    : m_sender(sender)
{
}

Connection *Request::sender() const
{
    return m_sender;
}

Request::~Request()
{
}

