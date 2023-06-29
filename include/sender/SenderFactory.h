#ifndef SENDERFACTORY_H
#define SENDERFACTORY_H

#include "Sender.h"

#include <string>

class SenderFactory 
{
    public:
        Sender* makeSender(std::string senderType);
};


#endif