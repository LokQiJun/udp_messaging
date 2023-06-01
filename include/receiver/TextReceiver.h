#ifndef TEXTRECEIVER_H
#define TEXTRECEIVER_H

#include "Receiver.h"

class TextReceiver : public Receiver
{
    public:
        TextReceiver();
        ~TextReceiver();

        boost::array<char, PACKET_SIZE> handleData();
};
#endif