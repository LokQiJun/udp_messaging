#ifndef FILESENDER_H
#define FILESENDER_H

#include "Sender.h"

// Reads a file and splits it into packets of data before passing it to Client class for transmission
class FileSender : public Sender
{
    public:
        FileSender(Client* client);
        ~FileSender() override;

        void send(std::string content) override;
};

#endif

