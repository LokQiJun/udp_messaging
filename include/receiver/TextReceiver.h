#ifndef TEXTRECEIVER_H
#define TEXTRECEIVER_H

#include "Receiver.h"

#include <fstream>

class TextReceiver : public Receiver
{
    public:
        TextReceiver(Server* server);
        ~TextReceiver() override;

        void receive() override;
};
#endif