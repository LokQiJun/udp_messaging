#ifndef TEXTSENDER_H
#define TEXTSENDER_H 

#include "Sender.h"

// Reads text message from user input and splits it into packets of data before passing it to Client class for transmission
class TextSender : public Sender
{
    public:
        TextSender(Client* client);
        ~TextSender() override;

        void send(std::string content) override;
};

#endif
