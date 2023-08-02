#ifndef SENDERFACTORY_H
#define SENDERFACTORY_H

#include "Sender.h"

#include <string>

// Factory design pattern implementation for all Sender classes
class SenderFactory 
{
    public:
        Sender* makeSender(std::string senderType);
};


#endif