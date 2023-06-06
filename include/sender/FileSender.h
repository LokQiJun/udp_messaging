#ifndef FILESENDER_H
#define FILESENDER_H

#include "Sender.h"

class FileSender : public Sender
{
    public:
        FileSender(Client* client);
        ~FileSender() override;

        void send(std::string content) override;
};
#endif
