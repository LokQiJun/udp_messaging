#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include "Receiver.h"

class FileReceiver : public Receiver
{
    public:
        FileReceiver();
        ~FileReceiver();

        void handleData(boost::array<char, PACKET_SIZE>& buffer, int bytesReceived, std::string filepath) override;
};

#endif