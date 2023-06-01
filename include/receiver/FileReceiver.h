#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include "Receiver.h"

class FileReceiver : public Receiver
{
    public:
        FileReceiver();
        ~FileReceiver();

        boost::array<char, PACKET_SIZE> handleData() override;
};

#endif