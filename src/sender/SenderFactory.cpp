#include "sender/SenderFactory.h"
#include "sender/TextSender.h"
#include "sender/FileSender.h"
#include "entities/Client.h"

Sender* SenderFactory::makeSender(std::string senderType)
{
    Client* client = Client::getInstance();

    if (strcmp(senderType.c_str(), "message"))
    {
        return new TextSender(client);
    }
    else if (strcmp(senderType.c_str(), "file"))
    {
        return new FileSender(client);
    }
    else
    {
        return nullptr;
    }
}