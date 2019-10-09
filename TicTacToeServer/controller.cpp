#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::onRequestOpened(const std::shared_ptr<Request> request)
{
    Connection * client = static_cast<Connection *>(sender());

    if (client == nullptr)
    {
        return;
    }
}
