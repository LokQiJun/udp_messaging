#ifndef TEXTRECEIVER_H
#define TEXTRECEIVER_H

#include "Receiver.h"

class TextReceiver : public Receiver
{
    public:
        TextReceiver();
        ~TextReceiver();

        void handleData(boost::array<char, PACKET_SIZE>& buffer, int bytesReceived) override;
};
#endif