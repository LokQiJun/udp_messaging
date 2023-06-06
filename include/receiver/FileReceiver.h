#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include "Receiver.h"

class FileReceiver : public Receiver
{
    public:
        FileReceiver(Server* server);
        ~FileReceiver() override;

        void receive() override;
};

#endif
