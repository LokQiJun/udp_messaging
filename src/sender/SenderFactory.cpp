#include "sender/SenderFactory.h"
#include "sender/TextSender.h"
#include "sender/FileSender.h"
#include "entities/Client.h"

Sender* SenderFactory::makeSender(std::string senderType)
{
    Client* client = Client::getInstance();

    if (strcmp(senderType.c_str(), "message") == 0)
    {
        return new TextSender(client);
    }
    else if (strcmp(senderType.c_str(), "file") == 0)
    {
        return new FileSender(client);
    }
    else
    {
        return nullptr;
    }
}